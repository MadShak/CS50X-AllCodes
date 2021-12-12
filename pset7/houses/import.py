from sys import argv
import cs50
import csv


if len(argv) != 2:
    print('Command: python import.py [file]')
    exit(1)

db = cs50.SQL("sqlite:///students.db")

# Open TSV file
# https://datasets.imdbws.com/title.basics.tsv.gz
with open(argv[-1], "r") as characters:

    # Create DictReader
    reader = csv.DictReader(characters)

    # Iterate over TSV file
    for r in reader:

        name = r['name'].split()
        first, middle, last = name[0], name[1] if len(name) == 3 else None, name[-1]

        birth = r['birth']
        house = r['house']

        # Insert show
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, house, birth)

