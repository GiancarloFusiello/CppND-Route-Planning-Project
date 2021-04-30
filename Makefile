help:
	@echo "build     - builds an image with the compiled application inside ready to be run"
	@echo "build-dev - builds an image with all of the project dependencies installed"
	@echo "            that can be used for development purposes."
	@echo "launch    - runs a container with the compiled application and launches the application."
	@echo "            The GUI can be viewed using a VNC client by connecting to localhost:5900"
	@echo "            and entering the password 'secret' if prompted"

build:
	docker-compose build route-planner

build-dev:
	docker-compose build route-planner-dev

launch:
	docker-compose run --rm --service-ports route-planner
	docker-compose down --volumes --remove-orphans
