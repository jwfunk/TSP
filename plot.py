import numpy as np
import pandas as pd

data = pd.read_csv("result.txt194")

print(data)

import matplotlib.pyplot as plt

fig=plt.figure()
ax=fig.add_axes([0,0,1,1])
ax.scatter(data['Y'], data['X'], color='r')
ax.set_title('scatter plot')
plt.plot(data['Y'],data['X'])
plt.show()
