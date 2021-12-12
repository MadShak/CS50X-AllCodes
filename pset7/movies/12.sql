-- write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred

SELECT title
FROM people JOIN stars ON stars.person_id = people.id JOIN movies ON movies.id = stars.movie_id
WHERE name = "Johnny Depp"
INTERSECT
SELECT title
FROM people JOIN stars ON stars.person_id = people.id JOIN movies ON movies.id = stars.movie_id
WHERE name = "Helena Bonham Carter"
