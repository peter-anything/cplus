FROM mysql:8

ENV TIME_ZONE Asia/Shanghai

RUN ln -sf /usr/share/zoneinfo/${TIME_ZONE} /etc/localtime

COPY my.cnf /etc/my.cnf

RUN chmod 644 /etc/my.cnf