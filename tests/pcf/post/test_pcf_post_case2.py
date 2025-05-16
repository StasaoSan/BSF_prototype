import requests

from config import BASE_URL_PCF, HEADERS


def test_pcf_post_case2():
    data = {
        "supi": "imsi-001011234567895",
        "macAddr48": "02:da:a3:0d:86:80",
        "dnn": "internet",
        "pcfIpEndPoints": [{"ipv4Address": "172.22.0.27", "port": 7777}],
        "snssai": {"sst": 1, "sd": 12345},
        "suppFeat": "2"
    }

    r = requests.post(BASE_URL_PCF, json=data, headers=HEADERS)
    json = r.json()
    assert r.status_code == 201, f"Expected 201, got {r.status_code}"
    assert "Location" in r.headers
    assert r.headers["Location"].startswith(BASE_URL_PCF)
    assert isinstance(json, dict) or isinstance(json, list)
