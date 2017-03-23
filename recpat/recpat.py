
# -*- coding: utf-8 -*-
"""
Created on Thu Mar 23 09:27:23 2017

@author:
"""

#==============================================================================
# n, dim = 300, 2
# np.random.seed(0)
# sigma_x=np.array([[1.5,0.2],[0.2,3.4]])
# eigenvals, Phi=np.linalg.eig(sigma_x)
# np.diag(eigenvals)
# np.diag(np.sqrt(1/eigenvals))
# 
# C = np.array([[0., -0.23], [0.83, .23]])
# X = np.r_[np.dot(np.random.randn(n, dim), C),
#               np.dot(np.random.randn(n, dim), C) + np.array([1, 1])]
# # y = np.hstack((np.zeros(n), np.ones(n)))
#==============================================================================
# %matplotlib qt
# %matplotlib inline
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import colors
from scipy.stats import multivariate_normal

def plot_cov_ellipse(cov, pos, volume=.5, ax=None, fc='none', ec=[0,0,0], a=1, lw=2):
    """
    Plots an ellipse enclosing *volume* based on the specified covariance
    matrix (*cov*) and location (*pos*). Additional keyword arguments are passed on to the 
    ellipse patch artist.

    Parameters
    ----------
        cov : The 2x2 covariance matrix to base the ellipse on
        pos : The location of the center of the ellipse. Expects a 2-element
            sequence of [x0, y0].
        volume : The volume inside the ellipse; defaults to 0.5
        ax : The axis that the ellipse will be plotted on. Defaults to the 
            current axis.
    """

    import numpy as np
    from scipy.stats import chi2
    import matplotlib.pyplot as plt
    from matplotlib.patches import Ellipse

    def eigsorted(cov):
        vals, vecs = np.linalg.eigh(cov)
        order = vals.argsort()[::-1]
        return vals[order], vecs[:,order]

    if ax is None:
        ax = plt.gca()

    vals, vecs = eigsorted(cov)
    theta = np.degrees(np.arctan2(*vecs[:,0][::-1]))

    kwrg = {'facecolor':fc, 'edgecolor':ec, 'alpha':a, 'linewidth':lw}

    # Width and height are "full" widths, not radius
    width, height = 2 * np.sqrt(chi2.ppf(volume,2)) * np.sqrt(vals)
    ellip = Ellipse(xy=pos, width=width, height=height, angle=theta, **kwrg)

    ax.add_artist(ellip)

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

#x, y = np.mgrid[-10:10:.1, -10:10:.1]
#pos = np.empty(x.shape + (2,))
#pos[:, :, 0] = x; pos[:, :, 1] = y
#rv_1 = multivariate_normal(mean_1, cov_1)
#rv_2 = multivariate_normal(mean_2, cov_2)
#plt.pcolormesh(x, y, np.where(rv_1 > rv_2), cmap='red_blue_classes', norm=colors.Normalize(0., 1.))
#np.where(rv_1 > rv_2)

plt.plot(x_1, y_1, 'o', color='blue', alpha=0.2,)
plt.plot(x_2, y_2, 'o', color='red', alpha=0.2,)
plot_cov_ellipse(cov_1, mean_1)
plot_cov_ellipse(cov_2, mean_2)
plt.axis('equal')
plt.show()


#
#plt.clf()
#x, y = np.mgrid[-1:1:.01, -1:1:.01]
#pos = np.empty(x.shape + (2,))
#pos[:, :, 0] = x; pos[:, :, 1] = y
#rv = multivariate_normal([0.5, -0.2], [[2.0, 0.3], [0.3, 0.5]])
#plt.contourf(x, y, rv.pdf(pos))


