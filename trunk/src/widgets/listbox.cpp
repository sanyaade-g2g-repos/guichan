/*
 *    _aaaa,  _aa.  sa,  aaa              _aaaa,_  ac  .aa.   .aa.  .aa,  _a, sa
 *  .wWV!!!T  |Wm;  dQ[  $WF            _mWT!"?Y  ]QE  :Q#:   ]QW[  :WWk. ]Q[ dW
 * .jWf       :WW: .dQ[  dQ[           .mW(       )WE  :Q#:  .mSQh. :mWQa.]W[ dQ
 * |QW:       :Wm;  mQ[  dQ[           ]Qk        )Qmi_aQW:  <B:$Qc :WBWQ()W[ dQ
 * |W#:  .ww  ;WW;  dQ[  dQ[  .......  ]Qk        )QB?YYW#:  jf ]Qp.:mE)Qm]Q[ )W
 * +WQ;  :Wm  |Wm; .mQ[  dQ[ :qgggggga ]Qm.       ]WE  :Q# :=QasuQm;:Wk 3QQW[ )Y
 *  ]Wmi.:Wm  +$Q; .mW(  dQ[  !"!!"!!^ dQk,  ._   ]WE  :Q# :3D"!!$Qc.Wk -$WQ[   
 *   "?????? ` "?!=m?!   ??'            -??????!  -?!  -?? -?'   "?"-?"  "??' "?
 *
 * Copyright (c) 2004 darkbits                              Js_./
 * Per Larsson a.k.a finalman                          _RqZ{a<^_aa
 * Olof Naess�n a.k.a jansem/yakslem                _asww7!uY`>  )\a//
 *                                                 _Qhm`] _f "'c  1!5m
 * Visit: http://guichan.darkbits.org             )Qk<P ` _: :+' .'  "{[
 *                                               .)j(] .d_/ '-(  P .   S
 * License: (BSD)                                <Td/Z <fP"5(\"??"\a.  .L
 * Redistribution and use in source and          _dV>ws?a-?'      ._/L  #'
 * binary forms, with or without                 )4d[#7r, .   '     )d`)[
 * modification, are permitted provided         _Q-5'5W..j/?'   -?!\)cam'
 * that the following conditions are met:       j<<WP+k/);.        _W=j f
 * 1. Redistributions of source code must       .$%w\/]Q  . ."'  .  mj$
 *    retain the above copyright notice,        ]E.pYY(Q]>.   a     J@\
 *    this list of conditions and the           j(]1u<sE"L,. .   ./^ ]{a
 *    following disclaimer.                     4'_uomm\.  )L);-4     (3=
 * 2. Redistributions in binary form must        )_]X{Z('a_"a7'<a"a,  ]"[
 *    reproduce the above copyright notice,       #}<]m7`Za??4,P-"'7. ).m
 *    this list of conditions and the            ]d2e)Q(<Q(  ?94   b-  LQ/
 *    following disclaimer in the                <B!</]C)d_, '(<' .f. =C+m
 *    documentation and/or other materials      .Z!=J ]e []('-4f _ ) -.)m]'
 *    provided with the distribution.          .w[5]' _[ /.)_-"+?   _/ <W"
 * 3. Neither the name of darkbits nor the     :$we` _! + _/ .        j?
 *    names of its contributors may be used     =3)= _f  (_yQmWW$#(    "
 *    to endorse or promote products derived     -   W,  sQQQQmZQ#Wwa]..
 *    from this software without specific        (js, \[QQW$QWW#?!V"".
 *    prior written permission.                    ]y:.<\..          .
 *                                                 -]n w/ '         [.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT       )/ )/           !
 * HOLDERS AND CONTRIBUTORS "AS IS" AND ANY         <  (; sac    ,    '
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING,               ]^ .-  %
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF            c <   r
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR            aga<  <La
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE          5%  )P'-3L
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR        _bQf` y`..)a
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,          ,J?4P'.P"_(\?d'.,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES               _Pa,)!f/<[]/  ?"
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT      _2-..:. .r+_,.. .
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     ?a.<%"'  " -'.a_ _,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION)                     ^
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "guichan/widgets/listbox.hpp"
#include "guichan/basiccontainer.hpp"
#include "guichan/widgets/scrollarea.hpp"

#include <iostream>

namespace gcn
{
  ListBox::ListBox()
  {    
    mSelected = -1;
    mListModel = NULL;
    setWidth(100);
    setFocusable(true);
    
    addMouseListener(this);
    addKeyListener(this);
  }

  ListBox::ListBox(ListModel *listModel)
  {
    mSelected = -1;
    setWidth(100);
    setListModel(listModel);
    setFocusable(true);
    
    addMouseListener(this);
    addKeyListener(this);
  }

  void ListBox::draw(Graphics* graphics)
  {
    graphics->setColor(getBackgroundColor());
    graphics->fillRectangle(Rectangle(0, 0, getWidth(), getHeight()));

    if (mListModel == NULL)      
    {
      return;
    }
    
    graphics->setColor(getForegroundColor());
    graphics->setFont(getFont());    
    
    int i, fontHeight;
    int y = 0;
    
    fontHeight = getFont()->getHeight();
    
    /**
     * @todo Check cliprects so we do not have to iterate over elements in the list model
     */
    for (i = 0; i < mListModel->getNumberOfElements(); ++i)
    {      
      if (i == mSelected)
      {
        graphics->drawRectangle(Rectangle(0, y, getWidth(), fontHeight));
      }
      
      graphics->drawText(mListModel->getElementAt(i), 1, y);      

      y += fontHeight;
    }
    
  } // end draw
  
  void ListBox::logic()
  {
    adjustSize();
    
  } // end logic

  int ListBox::getSelected()
  {
    return mSelected;

  } // end getSelected

  void ListBox::setSelected(int selected)
  {
    if (mListModel == NULL)
    {
      mSelected = -1;
    }
    else
    {
      if (selected < 0)
      {
        mSelected = -1;
      }
      else if (selected >= mListModel->getNumberOfElements())
      {
        mSelected = mListModel->getNumberOfElements() - 1;
      }
      else
      {
        mSelected = selected;
      }

      if (typeid(*getParent()) == typeid(ScrollArea))
      {
        ScrollArea* scrollArea = (ScrollArea*)getParent();
        Rectangle scroll;
        scroll.y = getFont()->getHeight() * mSelected;
        scroll.height = getFont()->getHeight();
        scrollArea->scrollToRectangle(scroll);
      }
    }

  } // end setSelected

  void ListBox::keyPress(const Key& key)
  {    
    if (key.getValue() == Key::ENTER || key.getValue() == Key::SPACE)
    {
      generateAction();
    }
    else if (key.getValue() == Key::UP)
    {      
      setSelected(mSelected - 1);

      if (mSelected == -1)
      {
        setSelected(0);
      }

      generateAction();
    }
    else if (key.getValue() == Key::DOWN)
    {
      setSelected(mSelected + 1);
      generateAction();
    }

  } // end keyPress

  void ListBox::mousePress(int x, int y, int button)
  {
    if (button == MouseInput::LEFT && hasMouse())
    {
      setSelected(y / getFont()->getHeight());
      generateAction();
    }
  } // end mousePress

  void ListBox::setListModel(ListModel *listModel)
  {
    mSelected = -1;
    mListModel = listModel;
    adjustSize();
    
  } // end setListModel
  
  ListModel* ListBox::getListModel()
  {
    return mListModel;
    
  } // end getListModel

  void ListBox::adjustSize()
  {
    if (mListModel != NULL)
    {      
      setHeight(getFont()->getHeight() * mListModel->getNumberOfElements());
    }
    
  } // end adjustSize
  
} // end gcn