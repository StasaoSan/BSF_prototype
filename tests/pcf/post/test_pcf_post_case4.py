import requests
from config import BASE_URL_PCF, HEADERS


def test_pcf_post_case4():
    data = {
        "supi": "imsi-001011234567895",
        "dnn": "internet",
        "pcfIpEndPoints": [{"ipv4Address": "172.22.0.27", "port": 7777}],
        "snssai": {"sst": 1, "sd": 12345},
        "suppFeat": "2"
    }

    r = requests.post(BASE_URL_PCF, json=data, headers=HEADERS)
    assert r.status_code == 400, f"Expected 400, got {r.status_code}"