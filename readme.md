# Encoding and Decoding JUAN file format

This project provides a command-line application that allows users to encode and decode images using the highly efficient Juan file format.

### Decoding

To decode an image, use the following command format:

<command> [NOMBRE_ARCHIVO_LECTURA] [NOMBRE_ARCHIVO_ESCRITURA] [ID] [DATE]

`Example: ./A encode ../img/raw/boat.bmp ../img/encoded/compressedImg.juan 10101 2024-04-07T23:09:15Z`

### Decoding

<command> [NOMBRE_ARCHIVO_COMPRIMIDO] [NOMBRE_ARCHIVO_RAW]

`Example: ./A decode ../img/encoded/compressedImg.juan ../img/raw/boat2.bmp`
