FROM ubuntu:16.04

# Instala o CMAKE
RUN apt-get update

# Copia tudo para o container
COPY . /vss-joystick
WORKDIR /vss-joystick

# Adiciona permissão de execução dos shellscripts
RUN chmod +x /vss-joystick/configure.sh
RUN chmod +x /vss-joystick/entrypoint.sh
RUN chmod +x /vss-joystick/install_core.sh

# Executa a instalação na criação dos containers
RUN /vss-joystick/install_core.sh
RUN /vss-joystick/configure.sh development

# Script executado no docker run
ENTRYPOINT ["/vss-joystick/entrypoint.sh"]