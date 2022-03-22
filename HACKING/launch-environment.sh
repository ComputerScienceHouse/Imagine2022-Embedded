#!/bin/bash
IMAGINE_DIR=/home/$USER/Code/ImagineRIT2022
mkdir -p "$IMAGINE_DIR"
podman run --rm -it                             \
    --name=imaginerit-embedded-dev              \
    --device=/dev/ttyUSB0:/dev/ttyUSB0:rwm      \
    --device=/dev/ttyUSB1:/dev/ttyUSB1:rwm      \
    -v "$IMAGINE_DIR":/ImagineRIT2022           \
    --group-add keep-groups                     \
    --annotation io.crun.keep_original_groups=1 \
    imaginerit-embedded-dev
#podman exec -it imaginerit-embedded-dev bash
