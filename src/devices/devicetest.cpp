/* This file is part of Clementine.

   Clementine is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Clementine is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Clementine.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "devicetest.h"
#include "devicekitlister.h"

#include <QtDebug>

DeviceTest::DeviceTest(QObject *parent)
  : QObject(parent)
{
  DeviceLister* lister = new DeviceKitLister;
  listers_ << lister;
  connect(lister, SIGNAL(DeviceAdded(QString)), SLOT(DeviceAdded(QString)));
  connect(lister, SIGNAL(DeviceRemoved(QString)), SLOT(DeviceRemoved(QString)));
  connect(lister, SIGNAL(DeviceChanged(QString)), SLOT(DeviceChanged(QString)));

  lister->Start();
}

DeviceTest::~DeviceTest() {
  qDeleteAll(listers_);
}

void DeviceTest::DeviceAdded(const QString &id) {
  DeviceLister* engine = qobject_cast<DeviceLister*>(sender());

  qDebug() << "Device added:" << id;
  for (int i=0 ; i<DeviceKitLister::LastField ; ++i) {
    qDebug() << i << engine->DeviceInfo(id, i);
  }
}

void DeviceTest::DeviceRemoved(const QString &id) {
  qDebug() << "Device removed:" << id;
}

void DeviceTest::DeviceChanged(const QString &id) {
  DeviceLister* engine = qobject_cast<DeviceLister*>(sender());

  qDebug() << "Device changed:" << id;
  for (int i=0 ; i<DeviceKitLister::LastField ; ++i) {
    qDebug() << i << engine->DeviceInfo(id, i);
  }
}
