# BSF Prototype for 5G Core

Prototype Binding Support Function (BSF) for the 5G Core.  
Implements Nbsf_Management API (3GPP TS 29.521) and self-registration in NRF (3GPP TS 29.510).

## 1. Code Generation

OpenAPI Generator CLI 7.7.0 can install via:

```bash
wget https://repo1.maven.org/maven2/org/openapitools/openapi-generator-cli/7.7.0/openapi-generator-cli-7.7.0.jar -O openapi-generator-cli.jar
```

### - nbsf-management: [TS29521_Nbsf_Management.yaml](openapi/TS29521_Nbsf_Management.yaml)
Use cpp-restbed-server and command:
```bash
java -jar openapi-generator-cli.jar generate -g cpp-restbed-server -i openapi/TS29521_Nbsf_management.yaml -o gen/nrf-nfm'
```

### - nrf-management: [TS29510_Nnrf_NFManagement.yaml](openapi/TS29510_Nnrf_NFManagement.yaml)
TS29510 not found correct ver of generator. cpp-restsdk generate with HTML sequenses instead of real symbols, for example [LinksValueSchema.cpp](gen/nrf-nfm-restsdk/src/model/LinksValueSchema.cpp)
(now changed / but in auto gen with cpp-restsdk errors there easiest to visible)

## 2. Run project:
### Two running optopns exists:
1. Devconcainer, build for VSCode, need to install devcontainer extenshion
2. docker (start with build.sh scrypt), after run build.sh:
   ```bash
    git clone https://github.com/StasaoSa`n/BSF_prototype.git
    cd BSF_prototype
    mkdir build && cd build
    cmake ..
    make
    ./bsf2 --config ../static_config.yaml`
    ```

## 3. Configuration:
You can edit [static_config.yaml](static_config.yaml) to configure server and build options.
### Note: 
bsf-reg part can be missed, or instead of nrf-addres can be specified scp-addres. If both - scp has hight priority.

```yaml
    server:
      listener:
        address: 0.0.0.0            # listening adress (default: localhost)
        port: 8080                  # listening port
        task_processor: main-task-processor
    ## ---
    bsf-reg:
      nrf-address: 127.0.0.1:7777   # where to do PUT request
      ipv4: 127.0.0.1               # BSF IP to others (PCF)
```

## 4. Supported API endpoints:

### 1. PCF BINDING:
- POST: 
  - URL: [host]:[port]/nbsf-management/v1/pcfBindings
    JSON: 
  ```json
  {"supi":"imsi-001011234567895","ipv4Addr":"182.108.1.0","macAddr48":"02:da:a3:0d:86:80","dnn":"internet","pcfIpEndPoints":[{"ipv4Address":"172.22.0.27","port":7777}],"snssai":{"sst":1,"sd":12345},"suppFeat":"2"}
  ```
- GET:
  - URL: [host]:[port]/nbsf-management/v1/pcfBindings?[params]
  - Answer - JSON
  - At least need one of:
    - ipv4Addr
    - macAddr48
  - Optional:
    - supi
    - dnn
    - snssai.sst
    - snssai.sd

- DELETE:
  - URL: [host]:[port]/nbsf-management/v1/pcfBindings/[bindingId]
  - bindingId can in headers request while POST: http://localhost:8080/nbsf-management/v1/pcfBindings/4963476939842138863

### 2. PCF UE BINDING:
- POST:
  - URL: [host]:[port]/nbsf-management/v1/pcf-ue-bindings
  - JSON: 
  ```json
  { "supi": "imsi-250020000000002", "gpsi": "msisdn-9001234567", "pcfForUeFqdn": "aaa://192.0.2.10:8888", "pcfForUeIpEndPoints": [ { "ipv4Address": "192.0.2.10", "port": 8888 } ], "pcfId": "9f0b3c12-1a34-45de-bd0a-2b2a8c0f96c1", "pcfSetId": "pcf-set-001" }
  ```
- GET:
  - URL: [host]:[port]/nbsf-management/v1/pcf-ue-bindings?[params]
  - Need one of (not double):
    - supi
    - gpsi

- DELETE:
  - nbsf-management/v1/pcf-ue-bindings/[bindingId]
  - bindingId can in headers request while POST: http://localhost:8080/nbsf-management/v1/pcf-ue-bindings/4963476939842134523

### 3. REGISTER BSF
- PUT:
  - Auto request when server starts
  - URL: [host]:[port]/nnrf-nfm/v1/nf-instances/[instanseId]
  - JSON:
  ```json
  { "nfInstanceId": "cab0beee-e57d-41ef-9cea-1ff0005e6996", "nfType": "BSF", "nfStatus": "REGISTERED", "ipv4Addresses": ["172.22.0.29"], "allowedNfTypes": ["SCP","PCF","AF"], "priority": 0, "capacity": 100, "load": 0, "nfServiceList": { "cab0d460-e57d-41ef-9cea-1ff0005e6996": { "serviceInstanceId": "cab0d460-e57d-41ef-9cea-1ff0005e6996", "serviceName": "nbsf-management", "versions": [ { "apiVersionInUri": "v1", "apiFullVersion": "1.0.0" } ], "scheme": "http", "nfServiceStatus": "REGISTERED", "ipEndPoints": [ { "ipv4Address": "172.22.0.29", "port": 7777 } ], "allowedNfTypes": [ "PCF", "AF" ], "priority": 0, "capacity": 100, "load": 0 } }, "nfProfileChangesSupportInd": true }
  ```
- DELETE:
  - URL [host]:[port]/nnrf-nfm/v1/nf-instances/[instanseId]


## 5. Tests
Can run in tests dir via pytest -v (need to preinstall libs: subprocess, pytest, requests)