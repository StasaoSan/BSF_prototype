import requests

from config import BASE_URL_PCF_UE, HEADERS


def test_valid_post_ue():
    data = {
        "supi": "imsi-012345678901234",
        "gpsi": "gpsi-001",
        "pcfForUeFqdn": "aaa://192.168.1.1:1234"
    }

    r = requests.post(BASE_URL_PCF_UE, json=data, headers=HEADERS)
    assert r.status_code == 201
    if r.content:
        assert isinstance(r.json(), dict)