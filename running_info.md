para set up el environment:

`conda create --prefix ./env python=3.9 ` o la version que use
`conda activate ./env` -> ahi adentro instalo todos los paquetes usando conda o pip.

`docker run --init -it --rm --name vivado_container --mount type=bind,source="/Volumes/denise_apfs/vivado-on-silicon-mac-main",target="/home/user" -p 127.0.0.1:5901:5901 --platform linux/amd64 x64-linux sudo -H -u user bash /home/user/scripts/install_vivado.sh`
