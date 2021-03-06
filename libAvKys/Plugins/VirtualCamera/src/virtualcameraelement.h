/* Webcamoid, webcam capture application.
 * Copyright (C) 2016  Gonzalo Exequiel Pedone
 *
 * Webcamoid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Webcamoid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Webcamoid. If not, see <http://www.gnu.org/licenses/>.
 *
 * Web-Site: http://webcamoid.github.io/
 */

#ifndef VIRTUALCAMERAELEMENT_H
#define VIRTUALCAMERAELEMENT_H

#include <QVariantMap>
#include <akelement.h>

class VirtualCameraElementPrivate;
class AkCaps;

class VirtualCameraElement: public AkElement
{
    Q_OBJECT
    Q_PROPERTY(QStringList driverPaths
               READ driverPaths
               WRITE setDriverPaths
               RESET resetDriverPaths
               NOTIFY driverPathsChanged)
    Q_PROPERTY(QStringList medias
               READ medias
               NOTIFY mediasChanged)
    Q_PROPERTY(QString media
               READ media
               WRITE setMedia
               RESET resetMedia
               NOTIFY mediaChanged)
    Q_PROPERTY(QList<int> streams
               READ streams
               NOTIFY streamsChanged)
    Q_PROPERTY(int maxCameras
               READ maxCameras
               NOTIFY maxCamerasChanged)
    Q_PROPERTY(QString rootMethod
               READ rootMethod
               WRITE setRootMethod
               RESET resetRootMethod
               NOTIFY rootMethodChanged)
    Q_PROPERTY(QStringList availableMethods
               READ availableMethods
               NOTIFY availableMethodsChanged)
    Q_PROPERTY(QString outputLib
               READ outputLib
               WRITE setOutputLib
               RESET resetOutputLib
               NOTIFY outputLibChanged)

    public:
        explicit VirtualCameraElement();
        ~VirtualCameraElement();

        Q_INVOKABLE QStringList driverPaths() const;
        Q_INVOKABLE QStringList medias() const;
        Q_INVOKABLE QString media() const;
        Q_INVOKABLE QList<int> streams() const;
        Q_INVOKABLE int maxCameras() const;
        Q_INVOKABLE QString rootMethod() const;
        Q_INVOKABLE QStringList availableMethods() const;
        Q_INVOKABLE QString outputLib() const;

        Q_INVOKABLE int defaultStream(const QString &mimeType) const;
        Q_INVOKABLE QString description(const QString &media) const;
        Q_INVOKABLE AkCaps caps(int stream) const;
        Q_INVOKABLE QVariantMap addStream(int streamIndex,
                                          const AkCaps &streamCaps,
                                          const QVariantMap &streamParams=QVariantMap());
        Q_INVOKABLE QVariantMap updateStream(int streamIndex,
                                             const QVariantMap &streamParams=QVariantMap());
        Q_INVOKABLE QString createWebcam(const QString &description="");
        Q_INVOKABLE bool changeDescription(const QString &webcam,
                                           const QString &description="") const;
        Q_INVOKABLE bool removeWebcam(const QString &webcam);
        Q_INVOKABLE bool removeAllWebcams();

    private:
        VirtualCameraElementPrivate *d;

    protected:
        QString controlInterfaceProvide(const QString &controlId) const;
        void controlInterfaceConfigure(QQmlContext *context,
                                       const QString &controlId) const;

    signals:
        void driverPathsChanged(const QStringList &driverPaths);
        void mediasChanged(const QStringList &medias) const;
        void mediaChanged(const QString &media);
        void streamsChanged(const QList<int> &streams);
        void maxCamerasChanged(int maxCameras);
        void rootMethodChanged(const QString &rootMethod);
        void availableMethodsChanged(const QStringList &availableMethods);
        void outputLibChanged(const QString &outputLib);
        void error(const QString &message);

    public slots:
        void setDriverPaths(const QStringList &driverPaths);
        bool addDriverPath(const QString &driverPath);
        bool addDriverPaths(const QStringList &driverPaths);
        bool removeDriverPath(const QString &driverPath);
        bool removeDriverPaths(const QStringList &driverPaths);
        void setMedia(const QString &media);
        void setRootMethod(const QString &rootMethod);
        void setOutputLib(const QString &outputLib);
        void resetDriverPaths();
        void resetMedia();
        void resetRootMethod();
        void resetOutputLib();
        void clearStreams();

        bool setState(AkElement::ElementState state);
        AkPacket iStream(const AkPacket &packet);

    private slots:
        void outputLibUpdated(const QString &outputLib);
        void rootMethodUpdated(const QString &rootMethod);
};

#endif // VIRTUALCAMERAELEMENT_H
