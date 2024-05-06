from math import log2
a, b, c = map(int, input().split())
print(str(2**a) + " % (" + str(2**b) + " - " + str(2**c) + ") = " + str(2**a % (2**b - 2**c)))
print(str(2**a) + " // (" + str(2**b) + " - " + str(2**c) + ") = " + str(2**a // (2**b - 2**c)))
print(str(2**a) + " // (" + str(2**b) + " - " + str(2**c) + ") = 2^" + str(log2(2**a // (2**b - 2**c))))
print(str(2**a % (2**b - 2**c))[-1])
print(str(2**a) + " % (" + str(2**b) + " - " + str(2**c) + ") = " + str(2**a % (2**b - 2**c)) + " = " + str(2**a) + " - " + str((2**b - 2**c) * (2**a // (2**b - 2**c))))