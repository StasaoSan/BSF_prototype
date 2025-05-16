# file for autostart binary file for cpp server
import time
import pytest
import requests
import serverControl
from config import BASE_URL_PCF, HEADERS

@pytest.fixture(scope="function", autouse=True)
def server():
    proc = serverControl.startServer()
    time.sleep(2)
    yield proc
    serverControl.stopServer(proc)


@pytest.fixture()
def prepare_pcf_binding():
    data = {
        "supi": "imsi-001011234567895",
        "ipv4Addr": "192.168.100.2",
        "macAddr48": "02:da:a3:0d:86:80",
        "ipv6Addr": "2b26:9c29:f084:04d5:e802:bf27:5a22:8aa6",
        "dnn": "internet",
        "pcfIpEndPoints": [{"ipv4Address": "172.22.0.27", "port": 7777}],
        "snssai": {"sst": 1, "sd": 12345},
        "suppFeat": "2"
    }
    r = requests.post(BASE_URL_PCF, json=data, headers=HEADERS)
    assert r.status_code == 201, f"Setup POST failed: {r.status_code}, {r.text}"
    return data