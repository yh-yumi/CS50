SELECT title FROM movies WHERE movies.id IN
(SELECT stars.movie_id FROM stars WHERE person_id =
(SELECT id FROM people WHERE name = "Johnny Depp"))
AND movies.id IN
(SELECT stars.movie_id FROM stars WHERE person_id =
(SELECT id FROM people WHERE name = "Helena Bonham Carter"));
-- WHERE movies.id IN ( ) AND movies.id IN ( ) select movies both stars share just like if (x = ...) and (x = ...)
-- It's a union not collection. And write complete expressions not x = 1 and 2

