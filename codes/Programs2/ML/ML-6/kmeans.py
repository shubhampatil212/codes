# Import necessary libraries
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.cluster import KMeans

# Step 1: Load the dataset
df = pd.read_csv('sales_data_sample.csv', encoding='unicode_escape')

# Step 2: Data Cleaning - Drop irrelevant columns
df = df.drop(['ADDRESSLINE1', 'ADDRESSLINE2', 'POSTALCODE', 'CITY', 'TERRITORY', 
              'PHONE', 'STATE', 'CONTACTFIRSTNAME', 'CONTACTLASTNAME', 'CUSTOMERNAME', 'ORDERNUMBER'], axis=1)

# Step 3: Encode Categorical Variables
label_cols = ['PRODUCTLINE', 'PRODUCTCODE', 'COUNTRY', 'DEALSIZE']
for col in label_cols:
    le = LabelEncoder()
    df[col] = le.fit_transform(df[col])

# Step 4: Normalize numerical data
scaler = StandardScaler()
df_scaled = pd.DataFrame(scaler.fit_transform(df), columns=df.columns)

# Step 5: Use the Elbow Method to determine optimal clusters
wcss = []
for k in range(1, 11):
    kmeans = KMeans(n_clusters=k, init='k-means++', max_iter=300, n_init=10, random_state=0)
    kmeans.fit(df_scaled)
    wcss.append(kmeans.inertia_)

# Plot the elbow graph
plt.plot(range(1, 11), wcss, marker='o')
plt.xlabel('Number of Clusters')
plt.ylabel('WCSS')
plt.title('Elbow Method for Optimal Clusters')
plt.grid(True)
plt.show()

# Step 6: Perform K-Means Clustering based on chosen k (e.g., k=4)
optimal_clusters = 4  # Example optimal k based on the elbow plot
kmeans = KMeans(n_clusters=optimal_clusters, init='k-means++', max_iter=300, n_init=10, random_state=0)
df['Cluster'] = kmeans.fit_predict(df_scaled)

# Step 7: Visualize Clusters (using first two dimensions as an example)
plt.scatter(df_scaled.iloc[:, 0], df_scaled.iloc[:, 1], c=df['Cluster'], cmap='viridis', marker='x')
plt.xlabel(df.columns[0])
plt.ylabel(df.columns[1])
plt.title(f'K-Means Clustering with {optimal_clusters} Clusters')
plt.colorbar()
plt.show()
