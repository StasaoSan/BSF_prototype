generate files:
openapi generator 7.7.0

nbsf-management: [TS29521_Nbsf_Management.yaml](openapi/TS29521_Nbsf_Management.yaml)
to generate use openapi-generator-cli, can install via "wget https://repo1.maven.org/maven2/org/openapitools/openapi-generator-cli/7.12.0/openapi-generator-cli-7.12.0.jar -O openapi-generator-cli.jar"

for nbsf-management use cpp-restbed-server and command:
java -jar openapi-generator-cli.jar generate -g cpp-restbed-server -i openapi/TS29521_Nbsf_management.yaml -o gen/nrf-nfm

for TS29510 not found correct ver of generator. cpp-restsdk generate with HTML sequenses instead of real symbols, for example [LinksValueSchema.cpp](gen/nrf-nfm-restsdk/src/model/LinksValueSchema.cpp)
(now changed/ but in auto gen with cpp-restsdk errors there easiest to visible)

for run you can chouse via:
1. docker (devconcainer)
2. docker (start with build.sh scrypt)

