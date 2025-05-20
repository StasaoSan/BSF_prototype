# file for autostart binary file for cpp server
import time
import pytest
import serverControl
import requests
from config import BASE_URL_PCF, HEADERS, BASE_URL_PCF_UE


@pytest.fixture(scope="function", autouse=True)
def server():
    proc = serverControl.startServer()
    time.sleep(2)
    yield proc
    serverControl.stopServer(proc)


# --------------- PCF BINDING FIXTURES
@pytest.fixture()
def pcf_json_data():
    return {
            "supi": "imsi-001011234567895",
            "ipv4Addr": "192.168.100.2",
            "macAddr48": "02:da:a3:0d:86:80",
            "ipv6Addr": "2b26:9c29:f084:04d5:e802:bf27:5a22:8aa6",
            "dnn": "internet",
            "pcfIpEndPoints": [{"ipv4Address": "172.22.0.27", "port": 7777}],
            "snssai": {"sst": 1, "sd": 12345},
            "suppFeat": "2"
           }

@pytest.fixture()
def prepare_pcf_binding(pcf_json_data):
    r = requests.post(BASE_URL_PCF, json=pcf_json_data, headers=HEADERS)
    assert r.status_code == 201, f"Setup POST failed: {r.status_code}, {r.text}"
    return pcf_json_data


@pytest.fixture()
def prepare_pcf_delete(pcf_json_data):
    r = requests.post(BASE_URL_PCF, json=pcf_json_data, headers=HEADERS)
    assert r.status_code == 201, f"Setup POST failed: {r.status_code}, {r.text}"
    return r.headers.get("Location").split("/")[-1]

# --------------- PCF UE BINDING FIXTURES
@pytest.fixture()
def pcf_ue_json_data():
    return {
            "supi": "imsi-250020000000002",
            "gpsi": "msisdn-9001234567",
            "pcfForUeFqdn": "aaa://192.0.2.10:8888",
            "pcfForUeIpEndPoints": [
              {
                "ipv4Address": "192.0.2.10",
                "port": 8888
              }
            ],
            "pcfId": "9f0b3c12-1a34-45de-bd0a-2b2a8c0f96c1",
            "pcfSetId": "pcf-set-001"
           }

@pytest.fixture()
def prepare_pcf_ue_binding(pcf_ue_json_data):
    r = requests.post(BASE_URL_PCF_UE, json=pcf_ue_json_data, headers=HEADERS)
    assert r.status_code == 201, f"Setup POST failed: {r.status_code}, {r.text}"
    return pcf_ue_json_data

@pytest.fixture()
def prepare_pcf_ue_delete(pcf_ue_json_data):
    r = requests.post(BASE_URL_PCF_UE, json=pcf_ue_json_data, headers=HEADERS)
    assert r.status_code == 201, f"Setup POST failed: {r.status_code}, {r.text}"
    return r.headers.get("Location").split("/")[-1]