# Seeing if the Kevlar data its the exponential distrubution well by constructing
# 1) A probability plot against the quantiles of an exponential distribution
# 2) By using a hanging rootogram

#1)
data = scan()
quantiles = vector(mode = "numeric", length = 101)
for (i in 1:101){
  # this is the inverse of the exponential cdf (-ln(1-x))
  quantiles[i] = -log(1-((i - .5)/101))
}
plot(quantiles, data, cex = .75, main = "Exponential QQ PLot", xlab = "Quantiles",
     ylab = "Observations")

qqline(data, distribution = qexp, col = "blue")

# 2)
#bin width chosen to be 1.13
binsVec = c(0.005, 1.135, 2.265, 3.395, 4.525, 5.655, 6.785, 7.915)

#finding Oi
observations = vector(mode = "numeric", length = 7)
for (i in 1:101){
  for (j in 1:length(binsVec)-1){
    if (data[i] <= binsVec[j + 1]){
      observations[j] = observations[j] + 1
      break
    }
  }
}

#finding Ei
lambda = 1/mean(data) #~0.9669
expectedValues = vector(mode = "numeric", length = 7)
for (i in 1:7){
  expectedValues[i] = 101 * (exp(-lambda * binsVec[i]) - exp(-lambda * binsVec[i+1]))
}

#heights of bins
final =  vector(mode = "numeric", length = 7)
for (i in 1:7){
  final[i] = sqrt(observations[i]) - sqrt(expectedValues[i])
}

#values for final heights of the rootogram
#[1] -0.07194643  0.57148813 -0.71822572 -0.56540855  0.09849137 -0.51917297  0.70101166
