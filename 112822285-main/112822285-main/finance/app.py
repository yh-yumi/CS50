import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares", type=int)
        user_shares = request.form.get("user_shares", type=int)
        # Throw out apologies when symbol is invalid
        if not symbol:
            return apology("Missing symbol", 403)
        # If no shares input or the sell number is more than what you have, throw out apologies
        if not shares:
            return apology("Missing shares", 403)
        elif shares > user_shares:
            return apology("Don't have that many Shares", 403)
        # Update cash number in database
        row = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = row[0]["cash"]
        cash += lookup(symbol)["price"] * shares
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])
        # Insert sell details to the purchase table
        db.execute("INSERT INTO purchase(user_id, symbol, symbolname, shares, price, date) VALUES(?, ?, ?, ?, ?, datetime('now'))",
                   session["user_id"], symbol, lookup(symbol)["name"], -shares, lookup(symbol)["price"])
        # Go back to the homepage
        return redirect("/")

    # Show portfolio of stocks
    else:

        # Select row to get the cash's value
        row = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        # The first row and go to the element that named cash
        cash = row[0]["cash"]
        # Select what I need to pass to the html file and return a list of rows
        portfolios = db.execute(
            "SELECT symbol, symbolname, SUM(shares) FROM purchase WHERE user_id = ? GROUP BY symbol", session["user_id"])

        stocks = []
        sum = cash
        # Make an empty list to store portfolios as a list of dictionaries and add another key-value that is price to the dictionary
        # portfolio is each row of list and each row is an element of dictionary
        # Use lookup to get the current price
        # Make sure the SUM(shares) in the table > 0 so it won't display the stocks you sold out
        # sum is the value I have right now
        for portfolio in portfolios:
            if portfolio['SUM(shares)'] > 0:
                stocks.append({"symbol": portfolio["symbol"],
                               "symbolname": portfolio["symbolname"],
                               "SUMshares": portfolio["SUM(shares)"],
                               "currentprice": lookup(portfolio["symbol"])["price"]
                               })
                sum += portfolio["SUM(shares)"] * (lookup(portfolio["symbol"])["price"])

        return render_template("index.html", cash=cash, stocks=stocks, sum=sum)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # When you click the submit button
    if request.method == "POST":
        symbol = request.form.get("symbol")
        # HTTP form data return a string, if use int(request.form.get("shares")) will get ValueError and return a 500 response if the value isn't an int.
        # Instead, use MultiDict.get().method and pass type=int to get the value if it exists and is an int.
        # shares will be set to integer or none if form doesn't exist or can't be converted into integers.
        shares = request.form.get("shares", type=int)
        # Throw out exceptions when don't get the inputs correctly.
        if not symbol:
            return apology("Missing Symbol", 400)
        elif not lookup(symbol):
            return apology("Invalid Symbol", 400)
        elif not shares:
            return apology("Missing Shares/Invalid number", 400)
        elif shares <= 0:
            return apology("Invalid Number", 400)

        row = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = row[0]["cash"]
        symbolprice = lookup(symbol)["price"]
        cash = cash - symbolprice * shares
        # If the cash you own is not enough, throw out an apology
        if cash < 0:
            return apology("Not Enough Cash", 403)
        # Update usesr's cash after the purchase
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])
        # Insert the details of the purchase to the purchase table
        db.execute("INSERT INTO purchase(user_id, symbol, symbolname, shares, price, date) VALUES(?, ?, ?, ?, ?, datetime('now'))",
                   session["user_id"], symbol, lookup(symbol)["name"], shares, lookup(symbol)["price"])
        # Go back to the homepage
        return redirect("/")
    else:
        # Dispaly the buy page
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    portfolios = db.execute("SELECT symbol, symbolname, shares, price, date FROM purchase WHERE user_id = ?", session["user_id"])
    return render_template("history.html", portfolios=portfolios)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # If get the input
    if request.method == "POST":
        symbol = request.form.get("symbol")
        symbolInfo = lookup(symbol)
    # If the input is invalid
        if not symbol:
            return apology("Missing Symbol", 400)
        elif not symbolInfo:
            return ("Invalid Symbol", 400)
    # Take the info and display it on another page
        return render_template("quoted.html", symbolInfo=symbolInfo, symbol=symbol)
    # Display the quote page
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # If get the inputs
    if request.method == "POST":
        name = request.form.get("username")
        password = request.form.get("password")
        # Create a hash_password for the password you type in
        hash_password = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)

        confirmation = request.form.get("confirmation")
        # Throw out apologies if the requirements are not met
        if not name:
            return apology("must provide username", 400)
        elif not password:
            return apology("must provide password", 400)
        elif not confirmation:
            return apology("must provide second password", 400)
        elif password != confirmation:
            return apology("password must be the same", 400)
        elif db.execute("SELECT username FROM users WHERE username = ?", name):
            return apology("username has been used", 400)
        # Insert user's info into database
        db.execute("INSERT INTO users(username, hash) VALUES(?, ?)", name, hash_password)
        # Make an message when you redirect to the homepage
        flash("Registered!")
        return redirect("/")

    # Display the register page
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # If get the inputs of sell
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares", type=int)
        # Throw out apologies when symbol is invalid
        if not symbol:
            return apology("Missing symbol", 400)
        elif symbol == "symbol":
            return apology("Have to choose a symbol", 400)
        # Select the number of shares you have for the symbol from database
        userShares = db.execute("SELECT SUM(shares) FROM purchase WHERE symbol = ? AND user_id = ?", symbol, session["user_id"])
        # If no shares input or the sell number is more than what you have, throw out apologies
        if not shares:
            return apology("Missing shares", 400)
        elif shares > userShares[0]["SUM(shares)"]:
            return apology("Don't have that many Shares", 400)
        # Update cash number in database
        row = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = row[0]["cash"]
        cash += lookup(symbol)["price"] * shares
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])
        # Insert sell details to the purchase table
        db.execute("INSERT INTO purchase(user_id, symbol, symbolname, shares, price, date) VALUES(?, ?, ?, ?, ?, datetime('now'))",
                   session["user_id"], symbol, lookup(symbol)["name"], -shares, lookup(symbol)["price"])
        # Go back to the homepage
        return redirect("/")
    # Display the sell page
    else:
        symbols = db.execute("SELECT DISTINCT symbol FROM purchase WHERE user_id = ?", session["user_id"])
        return render_template("sell.html", symbols=symbols)

