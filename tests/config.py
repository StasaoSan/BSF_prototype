BASE_URL_PCF = "http://localhost:8080/nbsf-management/v1/pcfBindings"
BASE_URL_PCF_UE = "http://localhost:8080/nbsf-management/v1/pcf-ue-bindings"

HEADERS = {"Content-Type": "application/json"}

BSF_BINARY = "/home/tikhonov-a/CLionProjects/BSF_prototype/cmake-build-debug/BSF2"
BSF_CONFIG = "/home/tikhonov-a/CLionProjects/BSF_prototype/static_config.yaml"

BASE_PCF_BINDING_JSON = \
{
    "supi": "imsi-001011234567895",
    "ipv4Addr": "192.168.100.2",
    "macAddr48": "02:da:a3:0d:86:80",
    "ipv6Addr": "2b26:9c29:f084:04d5:e802:bf27:5a22:8aa6",
    "dnn": "internet",
    "pcfIpEndPoints": [{"ipv4Address": "172.22.0.27", "port": 7777}],
    "snssai": {"sst": 1, "sd": 12345},
    "suppFeat": "2"
}

BASE_PCF_UE_BINDING_JSON = \
{
    "supi": "imsi-250020000000002",
    "gpsi": "msisdn-9001234567",
    "pcfForUeFqdn": "aaa://192.0.2.10:8888",
    "pcfForUeIpEndPoints":
        [
            {
                "ipv4Address": "192.0.2.10",
                "port": 8888
            }
        ],
    "pcfId": "9f0b3c12-1a34-45de-bd0a-2b2a8c0f96c1",
    "pcfSetId": "pcf-set-001"
}