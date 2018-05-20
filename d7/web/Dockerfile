FROM php:7.0-apache

# install the PHP extensions we need
RUN set -ex; \
  \
  if command -v a2enmod; then \
    a2enmod rewrite; \
  fi; \
  \
  savedAptMark="$(apt-mark showmanual)"; \
  \
  apt-get update; \
  apt-get install -y --no-install-recommends \
    libjpeg-dev \
    libpng-dev \
    libpq-dev \
  ; \
  \
  docker-php-ext-configure gd --with-png-dir=/usr --with-jpeg-dir=/usr; \
  docker-php-ext-install -j "$(nproc)" \
    gd \
    exif \
    opcache \
    pdo_mysql \
    zip \
  ; \
  \
# reset apt-mark's "manual" list so that "purge --auto-remove" will remove all build dependencies
  apt-mark auto '.*' > /dev/null; \
  apt-mark manual $savedAptMark; \
  ldd "$(php -r 'echo ini_get("extension_dir");')"/*.so \
    | awk '/=>/ { print $3 }' \
    | sort -u \
    | xargs -r dpkg-query -S \
    | cut -d: -f1 \
    | sort -u \
    | xargs -rt apt-mark manual; \
  \
  apt-get purge -y --auto-remove -o APT::AutoRemove::RecommendsImportant=false; \
  rm -rf /var/lib/apt/lists/*

# set recommended PHP.ini settings
# see https://secure.php.net/manual/en/opcache.installation.php
RUN { \
    echo 'opcache.memory_consumption=128'; \
    echo 'opcache.interned_strings_buffer=8'; \
    echo 'opcache.max_accelerated_files=4000'; \
    echo 'opcache.revalidate_freq=60'; \
    echo 'opcache.fast_shutdown=1'; \
    echo 'opcache.enable_cli=1'; \
  } > /usr/local/etc/php/conf.d/opcache-recommended.ini

ADD ./instance /var/www/html
RUN mkdir /var/www/scripts
ADD ./scripts /var/www/scripts

# Version
ENV COMPOSER_VERSION 1.6.5

# Let's roll
RUN  DEBIAN_FRONTEND=noninteractive curl -sSL https://getcomposer.org/installer \
   | php -- --install-dir=/usr/local/bin \
   --filename=composer --version=${COMPOSER_VERSION} && \
    chmod +x /usr/local/bin/composer && \
    echo 'export PATH="$PATH:$HOME/.composer/vendor/bin"' >> ~/.bashrc && \
    composer global require drush/drush:8.x

WORKDIR /var/www/html

RUN apt-get update && apt-get install -y mysql-client wget vim

RUN chown www-data:www-data -R /var/www/html && \
    find /var/www/html/ -type d -exec chmod 755 {} \; && \
    find /var/www/html/ -type f -exec chmod 755 {} \;&& \
    chmod -R 777 /var/www/html/sites/default/files && \
    find /var/www/scripts/ -type f -exec chmod 2755 {} \;

