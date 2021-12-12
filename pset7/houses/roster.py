from sys import argv
import cs50


if len(argv) != 2:
    print('Command: python roster.py [house]')
    exit(1)


db = cs50.SQL("sqlite:///students.db")
r = db.execute('SELECT * FROM students WHERE house = ? ORDER BY last, first', argv[-1])

for r in r:
    print(r['first'] + ' ' + (r['middle'] + ' ' if r['middle'] else '') + r['last'] + ', born ' + str(r['birth']))