
SELECT a.name FROM Track t
JOIN Album ab ON ab.AlbumId = t.AlbumId
JOIN Artist a ON ab.ArtistId = a.ArtistId
GROUP BY a.name
HAVING COUNT(*) > 5;

SELECT e.FirstName, e.LastName FROM Customer c 
JOIN Employee e ON c.SupportRepId = e.EmployeeId
GROUP BY e.employeeId
HAVING COUNT(*) > 5;


SELECT c.FirstName, Count(e.EmployeeId) From Customer c 
LEFT OUTER JOIN Employee e ON e.city = c.city
GROUP BY c.CustomerId;


SELECT t.Name  FROM Track t
WHERE t.Milliseconds >     
(SELECT AVG(Milliseconds) FROM Track);


SELECT c.CustomerId, e.EmployeeId FROM Customer c LEFT OUTER JOIN Employee e ON c.city = e.city;
select e.city from Employee e;

--- Here be chamuyo
CREATE VIEW generolistas(genero, cantidad) AS
SELECT g.name, COUNT(pt.PlaylistId) FROM Genre g

SELECT * FROM Genre g
JOIN Track t ON g.GenreId = t.GenreId
JOIN PlaylistTrack pt ON t.TrackId = pt.TrackId
GROUP BY g.GenreId;

SELECT r.name, COUNT(*) FROM
(SELECT * FROM Genre g
JOIN Track t ON g.GenreId = t.GenreId
JOIN PlaylistTrack pt ON t.TrackId = pt.TrackId
GROUP BY pt.PlaylistId) AS r
GROUP BY r.GenreId;

SELECT DISTINCT pt.PlaylistId FROM Genre g
JOIN Track t ON g.GenreId = t.GenreId
JOIN PlaylistTrack pt ON t.TrackId = pt.TrackId
WHERE g.Name = 'Rock'
GROUP BY pt.PlaylistId


FROM Playlist p

JOIN PlaylistTrack pt ON p.PlaylistId = pt.PlaylistId
JOIN Track t ON pt.TrackId = t.TrackId
JOIN Genre g ON t.GenreId = g.GenreId
GROUP BY g.GenreId, t.trackId;

--- Rodrigo

SELECT query1.name, query1.genre_id, count(query1.playlist_id) FROM
	(SELECT ge.name, ge.genre_id, pt.playlist_id
	FROM genre as ge
	JOIN track as tr ON tr.genre_id = ge.genre_id
	JOIN playlist_track as pt ON pt.track_id = tr.track_id 
	group by ge.genre_id, pt.playlist_id 
	order by ge.name desc) as query1 
group by query1.genre_id, query1.name 
order by count(query1.playlist_id);

select distinct pt.playlist_id, ge.genre_id, ge.name
from track as tr
join playlist_track as pt on pt.track_id = tr.track_id
join genre as ge on ge.genre_id = tr.genre_id order by ge.name desc;



