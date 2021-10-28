# 
#   dynamic port mappig doesn't work when the host network is used (--net=host).
#    -p 8000-9000:80 \
#

docker run --interactive --tty --rm \
    --network=host \
    --ipc=host \
    --privileged \
    --cap-add=ALL \
    --ulimit core=-1 \
    -v /var/run/docker.sock:/var/run/docker.sock \
    -v /etc/passwd:/etc/passwd:ro \
    -v /etc/group:/etc/group:ro \
    -v $HOME:$HOME \
    -e HOME=$HOME \
    -e USER=$USER \
    -u $(id -u $USER):$(id -g $USER) \
    --group-add $(getent group docker|cut -d":" -f3) \
    -w $PWD \
    dev:latest \
    /bin/bash --init-file $HOME/.profile
