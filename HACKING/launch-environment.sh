#!/bin/bash
IMAGINE_DIR=/home/thegreenone/Documents/imagine2022-embedded
mkdir -p "$IMAGINE_DIR"
podman run --rm -it                             \
    --name=imagine-embedded-dev                 \
    --device=/dev/ttyUSB0      \
    -v "$IMAGINE_DIR":/mnt/ImagineRIT2022       \
    --security-opt label=disable \
    --annotation run.oci.keep_original_groups=1 \
    --group-add keep-groups                     \
    imaginerit-embedded-dev
#     --annotation io.crun.keep_original_groups=1 \
#podman exec -it imaginerit-embedded-dev bash
