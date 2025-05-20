import pytest
import requests

BASE_URL_PCF = "http://localhost:8080/nbsf-management/v1/pcfBindings"
BASE_URL_PCF_UE = "http://localhost:8080/nbsf-management/v1/pcf-ue-bindings"

HEADERS = {"Content-Type": "application/json"}

BSF_BINARY = "/home/tikhonov-a/CLionProjects/BSF_prototype/cmake-build-debug/BSF2"
BSF_CONFIG = "/home/tikhonov-a/CLionProjects/BSF_prototype/static_config.yaml"
