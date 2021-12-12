# importing get_string from the cs50 library.
from cs50 import get_string


while True:

    # Declaring variables.
    words = 1
    sentences = 0
    alphabets = 0
    digits = 0
    special = 0
    evid = 0
    i = 0

    # Getting text.
    str = get_string('Txt: ')

    if (str):

        # Analyzing the text.
        for i in range(len(str)):

            if (str[i] == ' ' and str[i + 1]):
                words += 1

            elif (str[i] == '?' or str[i] == '!' or str[i] == '.'):
                sentences += 1

            elif (str[i].isalpha()):
                alphabets += 1

            elif (str[i].isnumeric()):
                digits += 1

            else:
                special += 1

        S = float(sentences / words * 100)
        A = float(alphabets / words * 100)

        # Measure how readable. Evidences (evid).
        evid = round((float)(0.0588 * A - 0.296 * S - 15.8))

        # Print grade result.
        if (evid < 1):
            print('Before Grade 1')

        elif (evid >= 16):
            print('Grade 16+')

        else:
            print('Grade ', evid)

    break