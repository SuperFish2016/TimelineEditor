#ifndef TIMELINETOOLBAR_H
#define TIMELINETOOLBAR_H

#include <QToolBar>
class QLabel;
class QLineEdit;
class QSlider;
class TimelineToolBar : public QToolBar
{
    Q_OBJECT

signals:
    void settingDialogClicked();
    void curveEditorDialogClicked();

    void openEasingCurveEditor();

    void playTriggered();
    void previousFrameTriggered();
    void nextFrameTriggered();
    void toFirstFrameTriggered();
    void toLastFrameTriggered();

    void recordToggled(bool val);
    void loopPlaybackToggled(bool val);

    void scaleFactorChanged(int value);
    void startFrameChanged(int value);
    void currentFrameChanged(int value);
    void endFrameChanged(int value);
public:
    explicit TimelineToolBar(QWidget *parent = nullptr);

    void reset();

    bool recording() const;
    int scaleFactor() const;
    QString currentTimelineId() const;

    void setCurrentState(const QString &name);
    void setBlockReflection(bool block);
    void setStartFrame(qreal frame);
    void setCurrentFrame(qreal frame);
    void setEndFrame(qreal frame);
    void setScaleFactor(int factor);

    void setActionEnabled(const QString &name, bool enabled);

    void openAnimationCurveEditor();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void createLeftControls();
    void createCenterControls();
    void createRightControls();
    void addSpacing(int width);
    void setupCurrentFrameValidator();

    QList<QObject *> m_grp;

    QLabel *m_timelineLabel = nullptr;
    QLabel *m_stateLabel = nullptr;
    QSlider *m_scale = nullptr;
    QLineEdit *m_firstFrame = nullptr;
    QLineEdit *m_currentFrame = nullptr;
    QLineEdit *m_lastFrame = nullptr;

    QAction *m_recording = nullptr;
    bool m_blockReflection = false;
};

#endif // TIMELINETOOLBAR_H
