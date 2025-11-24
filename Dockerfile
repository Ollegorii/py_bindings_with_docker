FROM python:3.10-slim

RUN apt-get update && apt-get install -y \
    cmake g++ python3-dev \
    && rm -rf /var/lib/apt/lists/*

RUN pip install numpy pybind11

WORKDIR /app

COPY svd.cpp svd.h bindings.cpp test_svd.py pyproject.toml CMakeLists.txt ./

RUN pip wheel . -w dist

# Компиляция pybind11-модуля
RUN c++ -O3 -shared -std=c++17 -fPIC \
    $(python3 -m pybind11 --includes) \
    bindings.cpp svd.cpp \
    -o svd_cpp$(python3-config --extension-suffix)

CMD ["python", "test_svd.py"]
