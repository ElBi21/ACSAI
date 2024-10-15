import numpy as np 
import cv2
from sklearn.cluster import KMeans

# Load the image first
image = cv2.imread("AI Lab/cat.jpeg")

# Store the shape of the image. Since scikit-learn allows to receive an input a single matrix,
# we are going to store the shape of the image, reshape the image into a mono-dimensional array
# and then restore the image to its original shape
height, width, chan_num = image.shape

# We can now create the KMeans instance

# By default KMeans has 8 classes, which means that our final image will have 8 colors.
# We can augment the number of colors by augmenting the number of classes
model = KMeans(n_clusters = 7)

# Now, let's reshape the image from 3D to 2D 
image2D = image.reshape(height * width, chan_num)

# Map the colors to the clusters
cluster_labels = model.fit_predict(image2D)

# Convert the centroid values into valid pixel values
bgr_colors = model.cluster_centers_.round(0).astype(int)

# Get back the 3D image
img_quant = np.reshape(bgr_colors[cluster_labels], (height, width, chan_num))
img_quant = img_quant.astype('uint8')

# Show the image
cv2.imshow("Compressed image", img_quant)
cv2.waitKey(0)
cv2.destroyAllWindows()