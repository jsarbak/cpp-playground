set -x
export USER_HOME=${HOME}
export USER_ID=$(id -u $USER)
export USER_GROUP_ID=$(id -g $USER)
export DOCKER_GROUP_ID=$(getent group docker|cut -d":" -f3)
docker-compose run --rm joedev-svc
