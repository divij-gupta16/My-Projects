library(geojsonio)
library(httr)
library(rgdal)
library(jsonlite)
library(mapview)
library(rgeos)
library(sp)

rm(list = ls())
setwd("/Users/Divij/Desktop/Geo IQ Data")

#Download geojsons/kmls from the API
geoiq_key = "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJtYWlsSWQiOiJzdXBwb3J0QGdlb2lxLmlvIn0.h2Nr3q9Xspe44dpVmjCIQyUggRgh7ShdxcT2HAt_K7g"
city_list = c("")#"Delhi","Bangalore","Chennai","Hyderabad","Kolkata","Jaipur")

query_params = list("key" = geoiq_key, "outputFileType" = "kml")
for(city in city_list){
  query_params = append(query_params,list("cityList" = city))
}
r <- GET("https://data2.geoiq.io/dataapis/v1.0/covid/hotspots", query = query_params)
r2 <- GET("https://data.geoiq.io/dataapis/v2.0/covid/availablecities", query = list("key" = geoiq_key))
r3 <- POST("https://data.geoiq.io/dataapis/v2.0/covid/availablecities", "*/*", "application/json", "key" = "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJtYWlsSWQiOiJzdXBwb3J0QGdlb2lxLmlvIn0.h2Nr3q9Xspe44dpVmjCIQyUggRgh7ShdxcT2HAt_K7g")
fileConn<-file(sprintf("%s.kml","Grouped"))
writeLines(content(r)["data"][[1]], fileConn)
close(fileConn)
kml_data = readOGR(sprintf("%s.kml","Grouped"))
kml_merged = gUnaryUnion(kml_data)
data = SpatialPolygonsDataFrame(kml_merged, data.frame(NA))
writeOGR(data, "/Users/Divij/Desktop/Geo IQ Data/Grouped.kml",layer="Grouped",driver="KML",overwrite_layer = T) 
kml_data2 = readOGR(sprintf("%s.kml","Grouped"))
mapview(kml_data2)
