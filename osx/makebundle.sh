#!/bin/sh

rm -rf ARABICON.app
rm -f *.app.zip

python $HOME/.local/bin/gtk-mac-bundler arabicon.bundle

echo "Compressing bundle"
#hdiutil create -format UDBZ -srcdir ARABICON.app -quiet ARABICON-2.9.6.1-$(git rev-parse --short master).dmg
zip -9rXq ./ARABICON-$(git describe --tags).app.zip ./ARABICON.app

