FROM python:3.10-slim

RUN apt-get update && apt-get install -y \
    cmake g++ python3-dev \
    && rm -rf /var/lib/apt/lists/*

RUN pip install pybind11 build

WORKDIR /app

COPY svd.cpp svd.h bindings.cpp pyproject.toml CMakeLists.txt test_svd.py ./

RUN python3 -m build --wheel

RUN pip install dist/*.whl

CMD ["python", "test_svd.py"]
