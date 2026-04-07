BUILD_DIR ?= build
BUILD_TYPE ?= Release

all: configure build

configure:
	@cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

build: configure
	@cmake --build $(BUILD_DIR)

rebuild: clean_build all

clean_build:
	@cmake --build $(BUILD_DIR) --target clean

clean:
	rm -rf $(BUILD_DIR) .venv

generate: .venv/.installed
	@cd ./tools && ./generate.sh

.venv/.installed: requirements.txt
	@python3 -m venv .venv
	@.venv/bin/pip install -q -r requirements.txt
	@touch .venv/.installed

# Run tests
test: BUILD_TYPE = Test
test: configure build
	build/tests/posthog-test $(ARGS)

.PHONY: all configure build rebuild clean_build clean generate test
