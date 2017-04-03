import numpy as np
import matplotlib.pyplot as plt
from matplotlib import colors
from scipy.stats import multivariate_normal

cmap = colors.LinearSegmentedColormap(
    'red_blue_classes',
    {'red': [(0, 1, 1), (1, 0.7, 0.7)],
     'green': [(0, 0.7, 0.7), (1, 0.7, 0.7)],
     'blue': [(0, 0.7, 0.7), (1, 1, 1)]})
plt.cm.register_cmap(cmap=cmap)

plt.clf()
mean_1 = [0, 0]
sigma_1=3.0
sigma_2=3.0
rho=-0.8

cov_1 = [[sigma_1**2, rho*sigma_1*sigma_2], [rho*sigma_1*sigma_2, sigma_2**2]]
x_1, y_1 = np.random.multivariate_normal(mean_1, cov_1, 500).T
mean_2 = [2.5, 4.5]
cov_2 = [[1.5, 0.2], [0.2, 2.5]]  # diagonal covariance
x_2, y_2 = np.random.multivariate_normal(mean_2, cov_2, 500).T

plt.plot(x_1, y_1, 'o', color='blue', alpha=0.2,)
plt.plot(x_2, y_2, 'o', color='red', alpha=0.2,)
plot_cov_ellipse(cov_1, mean_1)
plot_cov_ellipse(cov_2, mean_2)
plt.axis('equal')
plt.show()


