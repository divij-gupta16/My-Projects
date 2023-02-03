library(geojsonio)
library(httr)
library(rgdal)
library(jsonlite)
library(mapview)

rm(list = ls())
setwd("/Users/Divij/Desktop/Geo IQ Data")

#Download geojsons/kmls from the API
geoiq_key = "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJtYWlsSWQiOiJzdXBwb3J0QGdlb2lxLmlvIn0.h2Nr3q9Xspe44dpVmjCIQyUggRgh7ShdxcT2HAt_K7g"
city_list = c("Mumbai")

query_params = list("key" = geoiq_key,"outputFileType" = "kml")
for(city in city_list){
  query_params = append(query_params,list("cityList" = city))
}

r <- GET("https://data2.geoiq.io/dataapis/v1.0/covid/hotspots", query = list("cityList" = "Mumbai","key" = geoiq_key,"outputFileType" = "kml"))

fileConn<-file(sprintf("%s.kml","city_list"))
writeLines(content(r)["data"][[1]], fileConn)
close(fileConn)

length(content(r)["data"][[1]])

kml_data = readOGR(sprintf("%s.kml",city_list))

kml_data2 = kml_data[1:1900,]
writeOGR(kml_data2, "/Users/Divij/Desktop/Geo IQ Data/Mumbai1.kml",layer="CZ",driver="KML",overwrite_layer = T) 

kml_data3 = kml_data[1901:3521,]
writeOGR(kml_data3, "/Users/Divij/Desktop/Geo IQ Data/Mumbai2.kml",layer="CZ",driver="KML",overwrite_layer = T) 
