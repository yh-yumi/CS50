import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True
app.config["SESSION_TYPE"] = "filesystem"


# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():

    if request.method == "POST":

        # TODO: Add the user's entry into the database
        # request data from the input in the webpage and add to the database
        name = request.form.get("name")
        month = request.form.get("month", type = int)
        day = request.form.get("day", type = int)
        db.execute("INSERT INTO birthdays(name, month, day) VALUES(?, ?, ?)", name, month, day)
        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays = birthdays)

@app.route("/delete", methods = ["POST"])
def delete():
    id = request.form.get("id")
    if id:
        db.execute("DELETE FROM birthdays WHERE id = ?", id)
    return redirect("/")

@app.route("/edit", methods = ["POST"])
def edit():
    id = request.form.get("id")
    month = request.form.get("editmonth", type = int)
    day = request.form.get("editday", type = int)
    if id and month and day:
        db.execute("UPDATE birthdays SET month = ?, day = ? WHERE id = ?", month, day, id)
    return redirect("/")




