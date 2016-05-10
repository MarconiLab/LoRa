
if (!require("leaflet")) install.packages("leaflet")
if (!require("htmlwidgets")) install.packages("htmlwidgets")
if (!require("RSelenium")) install.packages("RSelenium")

library(leaflet)
library(htmlwidgets)
library(RSelenium)


# Choose file
myFile <- file.choose()
path_user <- dirname(myFile)
data <- read.csv(myFile, header = TRUE, sep = ',')


# Select only lines with GPS fix
data2 <- data[ which(data$Lat != 0),]

# Show the ID of measurements with GPS fix
print("These are the IDs of the measurements: ")
print(paste(unique(data$Id), collapse = ' '))

# Select ID
n <- readline("Enter the ID of the measurement you want to plot: ")
newdata <- data[ which(data$Id==n & data$Lat != 0),]

# Create directory if does not exist
newDir <- paste(path_user,"/",unique(newdata$Id), sep="")
ifelse(!dir.exists(newDir), dir.create(file.path(newDir)), FALSE)

# Plot RSSI time series
RSSIfilepath <- file.path(newDir, "RSSI.png")
png(RSSIfilepath)
valueRSSI <- cbind(ts(newdata$RSSI))
plot(valueRSSI, ylab="RSSI", xlab="Measurement", main="RSSI time series")
dev.off()


# Plot SNR time series
SNRfilepath <- file.path(newDir, "SNR.png")
png(SNRfilepath)
valueSNR <- cbind(ts(newdata$SNR))
plot(valueSNR, ylab="SNR", xlab="Measurement", main="SNR time series")
dev.off()

# Plot RSSI histogram
RSSIhistofilepath <- file.path(newDir, "RSSIhisto.png")
png(RSSIhistofilepath)
hist(newdata$RSSI, xlab = 'RSSI', ylab = 'Number Of Occurrences', main = "RSSI distribution", col="gray", border="white")
dev.off()


# Plot SNR histogram
SNRhistofilepath <- file.path(newDir, "SNRhisto.png")
png(SNRhistofilepath)
hist(newdata$SNR, xlab = 'SNR', ylab = 'Number Of Occurrences', main = "SNR distribution", col="gray", border="white")
dev.off()


# Mappa

mappafilepath <- file.path(newDir, "map.html")
m <- leaflet() %>%
  addTiles() %>%  # Add default OpenStreetMap map tiles
  addCircles(lng = newdata$Lng, lat = newdata$Lat)
saveWidget(m,mappafilepath, selfcontained = FALSE)
