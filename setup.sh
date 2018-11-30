
#!/bin/bash

sudo apt-get install imagemagick
sudo sed -i 's/rights="none"/rights="read|write"/g' /etc/ImageMagick-6/policy.xml

exit
