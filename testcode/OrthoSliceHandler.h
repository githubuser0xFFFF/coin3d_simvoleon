#ifndef CVRTEST_ORTHOSLICEHANDLER_H
#define CVRTEST_ORTHOSLICEHANDLER_H

#include <qwidget.h>

class SoOrthoSlice;
class SoOrthoSlice_ctrl;


class OrthoSliceHandler : QObject
{
  Q_OBJECT

public:
  OrthoSliceHandler(SoOrthoSlice * node, QWidget * parent = NULL);
  ~OrthoSliceHandler();

private slots:
  void sliceNumberEditUpdate(void);
//   void predefColorMapUpdate(int idx);

private:
  void initGUI(void);

  SoOrthoSlice * node;
  SoOrthoSlice_ctrl * ctrl;
};

#endif // !CVRTEST_ORTHOSLICEHANDLER_H
