import matplotlib.pyplot as plt

str_comp = []
hash_comp = []
coll = []

str_comp_mids = []
hash_comp_mids = []
coll_mids = []

str_comp_max = []
hash_comp_max = []
coll_max = []

str_comp_min = []
hash_comp_min = []
coll_min = []

with open("./files/data.csv") as f:
    for i in range(50):
        tmp = list(map(int, f.readline().split(';')))
        str_size = [3, 4, 5, 6, 7]
        str_comp.append(tmp[1])
        hash_comp.append(tmp[2])
        coll.append(tmp[3])
    print(hash_comp)
    
    for i in range(5):
        str_comp_mids.append(sum([m for m in str_comp[i*10:(i+1)*10]]) / 10)
        str_comp_max.append(max(str_comp[i*10:(i+1)*10]) - str_comp_mids[i])
        str_comp_min.append(str_comp_mids[i] - min(str_comp[i*10:(i+1)*10]))

        hash_comp_mids.append(sum([m for m in hash_comp[i*10:(i+1)*10]]) / 10)
        hash_comp_max.append(max(hash_comp[i*10:(i+1)*10]) - hash_comp_mids[i])
        hash_comp_min.append(hash_comp_mids[i] - min(hash_comp[i*10:(i+1)*10]))
        
        coll_mids.append(sum([m for m in coll[i*10:(i+1)*10]]) / 10)
        coll_max.append(max(coll[i*10:(i+1)*10]) - coll_mids[i])
        coll_min.append(coll_mids[i] - min(coll[i*10:(i+1)*10]))
        
    y_error_str = [str_comp_min, str_comp_max]
    y_error_hash = [hash_comp_min, hash_comp_max]
    y_error_coll = [coll_min, coll_max]
    
    plt.plot(str_size, str_comp_mids)
    plt.errorbar(str_size, str_comp_mids, yerr=y_error_str, fmt='o')

    plt.plot(str_size, hash_comp_mids)
    plt.errorbar(str_size, hash_comp_mids, yerr=y_error_hash, fmt='o')
    
    plt.plot(str_size, coll_mids)
    plt.errorbar(str_size, coll_mids, yerr=y_error_coll, fmt='o')

    plt.show()
    