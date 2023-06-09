SELECT title
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
JOIN ratings ON ratings.movie_id = movies.id --REMEMBER TO LINK RATINGS'S MOVIE_ID
WHERE name = "Chadwick Boseman" ORDER BY rating DESC LIMIT 5;