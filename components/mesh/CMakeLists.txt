idf_component_register(SRCS "mesh.c"
                            "mesh_netif.c"
                    REQUIRES udp nvs_flash lwip
                    INCLUDE_DIRS "." "include")
