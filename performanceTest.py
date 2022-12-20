import matplotlib.pyplot as plt

ccHashTable_alpha = [0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85,
                     0.9, 0.95, 1, 1.05, 1.1, 1.15, 1.2, 1.25, 1.3, 1.35, 1.4, 1.45]
ccHashTable_insert = [1, 1, 1, 1, 1, 1, 1, 1.1, 1.1, 1, 1.1, 1.3, 1, 1.5, 1.1, 1.5, 1.4, 1.1, 1.3, 1.1, 1.1, 1.3, 1.3,
                      1.4, 1.8, 1.6, 1.8, 2.2, 1.8, 1.3]
ccHashTable_search = [1, 1, 1, 1, 1.2, 1, 1.1, 1.5, 1.5, 1.2, 1.4, 1.9, 1.3, 2.2, 1.4, 2, 1.9, 1.9, 1.9, 1.6, 1.7, 1.9,
                      2.1, 1.8, 2.5, 2.3, 2.5, 3, 2.4, 1.8]
ccHashTable_remove = [1, 1, 1, 1, 1.2, 1, 1.1, 1.5, 1.5, 1.2, 1.4, 1.9, 1.3, 2.2, 1.4, 2, 1.9, 1.9, 1.9, 1.6, 1.7, 1.9,
                      2.1, 1.8, 2.5, 2.3, 2.5, 3, 2.4, 1.8]
ccHashTable_theoretical = [1, 1.025, 1.05, 1.075, 1.1, 1.125, 1.15, 1.175, 1.2, 1.225, 1.25, 1.275, 1.3, 1.325, 1.35, 1.375,
                           1.4, 1.425, 1.45, 1.475, 1.5, 1.525, 1.55, 1.575, 1.6, 1.625, 1.65, 1.675, 1.7, 1.725]
oaHashTable_alpha = [0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85,
                     0.9, 0.95]
oaHashTable_insert = [1, 1.2, 1, 1.6, 1, 1.8, 1.9, 2.3, 3.3, 2.6, 4, 4.4, 4.3, 5.3, 9.8, 12.4, 14.0, 16.3, 41.9, 163.8]
oaHashTable_search = [1, 1, 1, 1.2, 1.2, 1.2, 1.6, 1.5, 1.4, 1.8, 2.6, 2.8, 3.3, 8.4, 7.1, 7.1, 12.4, 22.1, 50.9, 196.1]
oaHashTable_remove = [1, 1, 1, 1.2, 1.2, 1.2, 1.6, 1.5, 1.4, 1.8, 2.6, 2.8, 3.3, 8.4, 7.1, 7.1, 12.4, 22.1, 50.9, 196.1]
oaHashTable_theoretical = [1, 1.05402, 1.11728, 1.19204, 1.28125, 1.38889, 1.52041, 1.68343, 1.88889, 2.15289, 2.5,
                           2.96914, 3.625, 4.58163, 6.05556, 8.5, 13, 22.7222, 50.5, 200.5]
plt.figure()
plt.ylabel('Counter number')
plt.xlabel('alpha')
plt.semilogy(ccHashTable_alpha, ccHashTable_insert, label='ccHashTable insert')
plt.semilogy(ccHashTable_alpha, ccHashTable_remove, label='ccHashTable delete')
plt.semilogy(ccHashTable_alpha, ccHashTable_search, label='ccHashTable search')
plt.semilogy(ccHashTable_alpha, ccHashTable_theoretical, label='ccHashTable theoretical')
plt.semilogy(oaHashTable_alpha, oaHashTable_insert, label='oaHashTable insert')
plt.semilogy(oaHashTable_alpha, oaHashTable_remove, label='oaHashTable delete')
plt.semilogy(oaHashTable_alpha, oaHashTable_search, label='oaHashTable search')
plt.semilogy(oaHashTable_alpha, oaHashTable_theoretical, label='oaHashTable theoretical')
plt.grid()
plt.legend()
plt.savefig('performance_lg.png')
plt.figure()
plt.ylabel('Counter number')
plt.xlabel('alpha')
plt.plot(ccHashTable_alpha, ccHashTable_insert, label='ccHashTable insert')
plt.plot(ccHashTable_alpha, ccHashTable_remove, label='ccHashTable delete')
plt.plot(ccHashTable_alpha, ccHashTable_search, label='ccHashTable search')
plt.plot(ccHashTable_alpha, ccHashTable_theoretical, label='ccHashTable theoretical')
plt.plot(oaHashTable_alpha, oaHashTable_insert, label='oaHashTable insert')
plt.plot(oaHashTable_alpha, oaHashTable_remove, label='oaHashTable delete')
plt.plot(oaHashTable_alpha, oaHashTable_search, label='oaHashTable search')
plt.plot(oaHashTable_alpha, oaHashTable_theoretical, label='oaHashTable theoretical')
plt.grid()
plt.legend()
plt.savefig('performance.png')
