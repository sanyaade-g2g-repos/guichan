/*      _______   __   __   __   ______   __   __   _______   __   __                 
 *     / _____/\ / /\ / /\ / /\ / ____/\ / /\ / /\ / ___  /\ /  |\/ /\                
 *    / /\____\// / // / // / // /\___\// /_// / // /\_/ / // , |/ / /                 
 *   / / /__   / / // / // / // / /    / ___  / // ___  / // /| ' / /                  
 *  / /_// /\ / /_// / // / // /_/_   / / // / // /\_/ / // / |  / /                   
 * /______/ //______/ //_/ //_____/\ /_/ //_/ //_/ //_/ //_/ /|_/ /                    
 * \______\/ \______\/ \_\/ \_____\/ \_\/ \_\/ \_\/ \_\/ \_\/ \_\/                      
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
 * 3. Neither the name of Guichan nor the      :$we` _! + _/ .        j?
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

/*
 * For comments regarding functions please see the header file. 
 */

#include "guichan/exception.hpp"
#include "guichan/focushandler.hpp"
#include "guichan/gui.hpp"
#include "guichan/key.hpp"

namespace gcn
{
  
  Gui::Gui()
  {
    mTop = NULL;
    mInput = NULL;
    mGraphics = NULL;
    mFocusHandler = new FocusHandler();
    mTopHasMouse = false;
		mTabbing = true;
  } // end Gui

  Gui::~Gui()
  {
		if (Widget::widgetExists(mTop))
		{
			setTop(NULL);
		}
		
    delete mFocusHandler;

  } // end ~Gui
  
  void Gui::setTop(Widget* top)
  {
    if (mTop)
    {
      mTop->_setFocusHandler(NULL);
    }
    if (top)
    {
      top->_setFocusHandler(mFocusHandler);
    }
    
    mTop = top;

  } // end setTop

  Widget* Gui::getTop() const
  {
    return mTop;

  } // end getTop

  void Gui::setGraphics(Graphics* graphics)
  {
    mGraphics = graphics;

  } // end setGraphics

  Graphics* Gui::getGraphics() const
  {
    return mGraphics;

  } // end getGraphics

  void Gui::setInput(Input* input)
  {
    mInput = input;

  } // end setInput
  
  Input* Gui::getInput() const
  {
    return mInput;

  } // end getInput

  void Gui::logic()
  {
    if (!mTop)
    {
      throw GCN_EXCEPTION("Gui::logic. No top widget set");
    }

    if(mInput)
    {
			mInput->_pollInput();
			
      while (!mInput->isMouseQueueEmpty())
      {
        MouseInput mi = mInput->dequeueMouseInput();

        Widget* focused = mFocusHandler->getFocused();

        if (mi.x > 0 && mi.y > 0 && mTop->getDimension().isPointInRect(mi.x, mi.y))
        {
          if (!mTopHasMouse)
          {
            mTop->_mouseInMessage();
            mTopHasMouse = true;
          }
          
          MouseInput mio = mi;
          mio.x -= mTop->getX();
          mio.y -= mTop->getY();        
          
          mTop->_mouseInputMessage(mio);
        }
        else
        {
          if (mTopHasMouse)
          {
            mTop->_mouseOutMessage();
            mTopHasMouse = false;
          }
        }                

        if (mFocusHandler->getFocused() && focused == mFocusHandler->getFocused())
        {
          int xOffset, yOffset;
          mFocusHandler->getFocused()->getAbsolutePosition(xOffset, yOffset);

          MouseInput mio = mi;
          mio.x -= xOffset;
          mio.y -= yOffset;
          mFocusHandler->getFocused()->_mouseInputMessage(mio);
        }       

      } // end while

      while (!mInput->isKeyQueueEmpty())        
      {
        KeyInput ki = mInput->dequeueKeyInput();

				if (mTabbing
						&& ki.getKey().getValue() == Key::TAB
						&& ki.getType() == KeyInput::PRESS)
				{
					if (ki.getKey().isShiftPressed())
					{
						mFocusHandler->tabPrevious();
					}
					else
					{
						mFocusHandler->tabNext();
					}
				}
				else
				{
					// Send key inputs to the focused widgets
					if (mFocusHandler->getFocused())						
					{
						if (mFocusHandler->getFocused()->isFocusable())
						{
							mFocusHandler->getFocused()->_keyInputMessage(ki);
						}
						else
						{
							mFocusHandler->focusNone();
						}
					}
				}
										
        // Focus another widget only if the widget allows it with
        // tabable.
				
// 				if (mFocusHandler->getFocused())
// 				{
// 					if (mTabbing && mFocusHandler->getFocused()->isTabable()
// 							&& ki.getKey().getValue() == Key::TAB
// 							&& ki.getType() == KeyInput::PRESS
// 							&& ki.getKey().isShiftPressed())
// 					{
// 						mFocusHandler->focusPrevious();
// 					}                  
// 					else if (mTabbing && mFocusHandler->getFocused()->isTabable()
// 									 && ki.getKey().getValue() == Key::TAB
// 									 && ki.getType() == KeyInput::PRESS)
// 					{
// 						mFocusHandler->focusNext();
// 					}
// 					else
// 					{
// 				
// 					}
// 				}
// 				else if (mTabbing && ki.getKey().getValue() == Key::TAB &&
// 								 ki.getType() == KeyInput::PRESS &&
// 								 ki.getKey().isShiftPressed())
// 				{
// 					mFocusHandler->focusPrevious();
// 				}        
// 				else if (mTabbing && ki.getKey().getValue() == Key::TAB &&
// 								 ki.getType() == KeyInput::PRESS)
// 				{
// 					mFocusHandler->focusNext();
// 				}		
      }
      
    } // end if
    
    mTop->logic();
		
  } // end logic
	
  void Gui::draw()
  {
    if (!mTop)
    {
      throw GCN_EXCEPTION("Gui::draw. No top widget set");
    }
    if (!mGraphics)
    {
      throw GCN_EXCEPTION("Gui::draw. No graphics set");
    }

    mGraphics->_beginDraw();
    mGraphics->pushClipArea(mTop->getDimension());    
    mTop->draw(mGraphics);
    mGraphics->popClipArea();
    mGraphics->_endDraw();
    
  } // end draw

	void Gui::focusNone()
	{
		mFocusHandler->focusNone();
	}

	void Gui::setTabbingEnabled(bool tabbing)
	{
		mTabbing = tabbing;
	}
	
	bool Gui::isTabbingEnabled()
	{
		return mTabbing;
	}
	
} // end gcn