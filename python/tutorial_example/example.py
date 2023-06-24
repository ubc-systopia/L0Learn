import fastsparsegams
import sys

################################################
######## Linear Regression
import numpy as np

np.random.seed(4)  # fix the seed to get a reproducible result
n, p, k = 500, 1000, 10
X = np.random.normal(size=(n, p))
B = np.zeros(p)
B[:k] = 1
e = np.random.normal(size=(n,)) / 2
y = X @ B + e


print("\nfitting linear regression with continuous feature")
fit_model = fastsparsegams.fit(X, y, penalty="L0", max_support_size=20)

with np.printoptions(threshold=10):
    print(fit_model.predict(x=X, lambda_0=0.032715, gamma=0))

fit_model_2 = fastsparsegams.fit(
    X,
    y,
    penalty="L0L2",
    num_gamma=5,
    gamma_min=0.0001,
    gamma_max=10,
    max_support_size=20,
)

with np.printoptions(threshold=10):
    print(fit_model_2.predict(x=X, lambda_0=0.0016, gamma=10))

################################################
######## Logistic Regression continuous feature
import numpy as np

np.random.seed(4)  # fix the seed to get a reproducible result
n, p, k = 500, 1000, 10
X = np.random.normal(size=(n, p))
B = np.zeros(p)
B[:k] = 1
e = np.random.normal(size=(n,)) / 2
y = np.sign(X @ B + e)

print("\nfitting logistic loss with continuous feature")
fit_model_3 = fastsparsegams.fit(
    X, y, loss="Logistic", max_support_size=20, algorithm="CDPSI"
)

print(fit_model_3.lambda_0)
lambda0 = fit_model_3.lambda_0[0][7]
print(np.where(fit_model_3.coeff(lambda_0=lambda0).toarray() > 1e-8)[0])
print(np.where(np.abs(fit_model_3.coeff(lambda_0=lambda0).toarray()) > 1e-8)[0])

with np.printoptions(threshold=10):
    print(fit_model_3.predict(X, lambda_0=lambda0))

###############################################
######## Logistic Regression binary feature
np.random.seed(4)  # fix the seed to get a reproducible result
n, p, k = 1000, 100, 10
X = np.random.randint(2, size=(n, p)).astype(float)
B = np.zeros(p)
B[: (k // 2)] = 1
B[(k // 2) : k] = -1
e = np.random.normal(size=(n,)) / 2
y = np.sign(X @ B + e)
print("\nfitting logistic loss with binary feature")
fit_model_3 = fastsparsegams.fit(
    X, y, loss="Logistic", max_support_size=20, algorithm="CDPSI"
)

print(fit_model_3.lambda_0)
lambda0 = fit_model_3.lambda_0[0][7]
print(np.where(fit_model_3.coeff(lambda_0=lambda0).toarray() > 1e-8)[0])
print(np.where(np.abs(fit_model_3.coeff(lambda_0=lambda0).toarray()) > 1e-8)[0])

with np.printoptions(threshold=10):
    print(fit_model_3.predict(X, lambda_0=lambda0))


################################################
######## Exponential Loss binary feature
np.random.seed(4)  # fix the seed to get a reproducible result
n, p, k = 1000, 100, 10
X = np.random.randint(2, size=(n, p)).astype(float)
B = np.zeros(p)
B[: (k // 2)] = 1
B[(k // 2) : k] = -1
e = np.random.normal(size=(n,)) / 2
y = np.sign(X @ B + e)

print("\nfitting exponential loss with binary feature")
fit_model_3 = fastsparsegams.fit(
    X, y, loss="Exponential", max_support_size=20, algorithm="CDPSI"
)

print(fit_model_3.lambda_0)
print("length of lambda_0 is {}".format(len(fit_model_3.lambda_0[0])))
lambda0 = fit_model_3.lambda_0[0][40]
print(np.where(fit_model_3.coeff(lambda_0=lambda0).toarray() > 1e-8)[0])
print(np.where(np.abs(fit_model_3.coeff(lambda_0=lambda0).toarray()) > 1e-8)[0])

with np.printoptions(threshold=10):
    print(fit_model_3.predict(X, lambda_0=lambda0))
