import matplotlib.pyplot as plt

data3 = [3, 168, 41.6, 370]
data4 = [4, 169.7, 45.3, 81]
data5 = [5, 171.8, 42.1, 11.6]
data6 = [6, 173.3, 43, 4.3]
data7 = [7, 173.9, 42.2, 0.7]

str_len = [3, 4, 5, 6, 7]
str_comp = [168, 169.7, 171.8, 173.3, 173.9]
hash_comp = [41.6, 45.3, 42.1, 43, 42.2]
coll = [370, 81, 11.6, 4.3, 0.7]

str_err = [i / 100 for i in str_comp]
hash_err = [i / 1000 for i in hash_comp]
coll_err = [i / 100 for i in coll]

print(str_err)

# plt.plot(str_len, str_comp)
# plt.errorbar(str_len, str_comp, yerr=str_err, fmt="o")

# plt.plot(str_len, hash_comp)
# plt.errorbar(str_len, hash_comp, yerr=5, fmt="o")

plt.plot(str_len, coll)
plt.errorbar(str_len, coll, yerr=40, fmt="o")

plt.show()