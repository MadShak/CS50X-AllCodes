# importing get_string from the cs50 library.
from sys import argv
# importing get_string from the cs50 library.
from csv import reader, DictReader


# Teaching how to useself.
if len(argv) < 3:

    print("Command: python dna.py [data.csv] [sequence.txt]")

    exit()

# Reading file.
with open(argv[2]) as dnafile:
    dnaLector = reader(dnafile)
    for row in dnaLector:
        dnalist = row

dna = dnalist[0]

# Store sequences.
sequences = {}

# Extracting from the database.
with open(argv[1]) as peopleFile:
    people = reader(peopleFile)
    for row in people:
        dnaSeq = row
        dnaSeq.pop(0)
        break

# Copy into a dictionary.
for item in dnaSeq:
    sequences[item] = 1

# Counts repetitions of dictionary values.
for key in sequences:

    l = len(key)
    temp = 0
    Max = 0

    for i in range(len(dna)):
        while temp > 0:
            temp -= 1
            continue

        if dna[i: i + l] == key:
            while dna[i - l: i] == dna[i: i + l]:
                temp += 1
                i += l

            if temp > Max:
                Max = temp

    sequences[key] += Max

# Treats each person as a dictionary to compare with the strings.
with open(argv[1], newline='') as peopleFile:
    people = DictReader(peopleFile)

    for person in people:
        match = 0

        for dna in sequences:
            if sequences[dna] == int(person[dna]):
                match += 1

        if match == len(sequences):
            print(person['name'])

            exit()

    print("No match")