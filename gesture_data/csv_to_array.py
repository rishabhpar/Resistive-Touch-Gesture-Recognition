import csv
data = []
with open('U.csv', 'r') as csvfile:
    reader = csv.reader(csvfile)
    for row in reader:
        row_pair = [int(val) for val in row]
        data.append(row_pair[0])
        data.append(row_pair[1])

print(data)