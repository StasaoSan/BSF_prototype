import requests

from config import BASE_URL_PCF, HEADERS


def test_pcf_post_case6():
    data = { }
    r = requests.post(BASE_URL_PCF, json=data, headers=HEADERS)
    assert r.status_code == 400, f"Expected 400, got {r.status_code}"
