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

#include "guichan/exception.hpp"
#include "guichan/widgets/dropdown.hpp"

#include <iostream>

namespace gcn
{  
	DropDown::DropDown()
	{
		mDroppedDown = false;
		mPushed = false;
    
		setWidth(100);
		setFocusable(true);

		mDefaultScrollArea = new ScrollArea();
		mDefaultScrollArea->setHorizontalScrollPolicy(ScrollArea::SHOW_NEVER);
		mDefaultListBox = new ListBox();

		mScrollArea = mDefaultScrollArea;
		mScrollArea->_setFocusHandler(&mFocusHandler);
		mScrollArea->_setParent(this);
		
		mListBox = mDefaultListBox;    
		mListBox->addActionListener(this);
		mScrollArea->setContent(mListBox);
        
		addMouseListener(this);
		addKeyListener(this);
		adjustHeight();
		
	} // end DropDown
    
	DropDown::DropDown(ListModel *listModel)
	{
		setWidth(100);
		setFocusable(true);
		mDroppedDown = false;
		mPushed = false;    
    
		mDefaultScrollArea = new ScrollArea();
		mDefaultScrollArea->setHorizontalScrollPolicy(ScrollArea::SHOW_NEVER);
		mDefaultListBox = new ListBox();

		mScrollArea = mDefaultScrollArea;
		mScrollArea->_setParent(this);
		mListBox = mDefaultListBox;
		mListBox->addActionListener(this);
			
		mScrollArea->setContent(mListBox);
		mScrollArea->_setFocusHandler(&mFocusHandler);
		mScrollArea->_setParent(this);
			
		setListModel(listModel);
    
		if (mListBox->getSelected() < 0)
		{
			mListBox->setSelected(0);
		}

		addMouseListener(this);
		addKeyListener(this);
		adjustHeight();
	} // end DropDown
  
	DropDown::DropDown(ListModel *listModel,
					   ScrollArea *scrollArea,
					   ListBox *listBox)
	{
		setWidth(100);
		setFocusable(true);
		mDroppedDown = false;
		mPushed = false;
    
		mDefaultScrollArea = NULL;
		mDefaultListBox = NULL;

		mScrollArea = scrollArea;
		mScrollArea->_setFocusHandler(&mFocusHandler);

		mListBox = listBox;    
		mListBox->addActionListener(this);
		mScrollArea->setContent(mListBox);
		mScrollArea->_setParent(this);
			
		setListModel(listModel);

		if (mListBox->getSelected() < 0)
		{
			mListBox->setSelected(0);
		}

		addMouseListener(this);
		addKeyListener(this);
		adjustHeight();
		
	} // end DropDown

	DropDown::~DropDown()
	{	  
		if (mScrollArea != NULL)
		{
			mScrollArea->_setFocusHandler(NULL);
		}

		if (mDefaultScrollArea != NULL)
		{
			delete mDefaultScrollArea;
		}

		if (mDefaultListBox != NULL)
		{
			delete mDefaultListBox;
		}

		if (widgetExists(mListBox))
		{
			mListBox->removeActionListener(this);
		}

	} // end ~DropDown
  
	void DropDown::logic()
	{
		if (mScrollArea == NULL || mScrollArea->getContent() == NULL)
		{
			throw GCN_EXCEPTION("DropDown::logic. ScrollArea or ListBox is NULL");
		}
	  
		mScrollArea->logic();    
	}
    
	void DropDown::draw(Graphics* graphics)
	{	 
		if (mScrollArea == NULL || mScrollArea->getContent() == NULL)
		{
			throw GCN_EXCEPTION("DropDown::draw. ScrollArea or ListBox is NULL");
		}

		int h;

		if (mDroppedDown)
		{
			h = mOldH;
		}
		else
		{
			h = getHeight();
		}
    
		int alpha = getBaseColor().a;
		Color faceColor = getBaseColor();
		faceColor.a = alpha;
		Color highlightColor = faceColor + 0x303030;
		highlightColor.a = alpha;
		Color shadowColor = faceColor - 0x303030;      
		shadowColor.a = alpha;    
		

		graphics->setColor(getBackgroundColor());
		graphics->fillRectangle(Rectangle(1, 1, getWidth() - 2, h - 2));
   
 		graphics->setColor(shadowColor);
 		graphics->drawLine(0, 0, 0, h);
 		graphics->drawLine(0, 0, getWidth()-1, 0);

 		graphics->setColor(highlightColor);           
 		graphics->drawLine(1, h - 1, getWidth() - 2, h - 1);
 		graphics->drawLine(getWidth()-1, 1, getWidth()-1, h - 1);


		graphics->setColor(getForegroundColor());
		graphics->setFont(getFont());
    
		if (mListBox->getListModel() && mListBox->getSelected() >= 0)
		{
			graphics->drawText(mListBox->getListModel()->getElementAt(mListBox->getSelected()), 2, 1);
		}

		if (hasFocus())
		{
			graphics->drawRectangle(Rectangle(1, 1, getWidth() - 1, h - 2));
		}
		
		drawButton(graphics);
            
 		if (mDroppedDown)
 		{
 			graphics->pushClipArea(mScrollArea->getDimension());
 			mScrollArea->draw(graphics);
 			graphics->popClipArea();
 		}
		
	} // end draw

	void DropDown::drawButton(Graphics *graphics)
	{
		Color faceColor, highlightColor, shadowColor;
		int offset;
		int alpha = getBaseColor().a;
		
		if (mPushed)
		{
			faceColor = getBaseColor() - 0x303030;
			faceColor.a = alpha;
			highlightColor = faceColor - 0x303030;
			highlightColor.a = alpha;
			shadowColor = faceColor + 0x303030;
			shadowColor.a = alpha;
			offset = 1;
		}
		else
		{
			faceColor = getBaseColor();
			faceColor.a = alpha;
			highlightColor = faceColor + 0x303030;
			highlightColor.a = alpha;
			shadowColor = faceColor - 0x303030;
			shadowColor.a = alpha;
			offset = 0;
		}

		int h;
		if (mDroppedDown)
		{
			h = mOldH - 2;
		}
		else
		{
			h = getHeight() - 2;
		}
		int x = getWidth() - h;
		int y = 1;    

		graphics->setColor(faceColor);
		graphics->fillRectangle(Rectangle(x+1, y+1, h-2, h-2));

		graphics->setColor(highlightColor);
		graphics->drawLine(x, y, x+h-1, y);
		graphics->drawLine(x, y+1, x, y+h-1);

		graphics->setColor(shadowColor);
		graphics->drawLine(x+h-1, y+1, x+h-1, y+h-1);
		graphics->drawLine(x+1, y+h-1, x+h-2, y+h-1);

		graphics->setColor(getForegroundColor());
    
		int i;
		int hh = h / 3;
		int hx = x + h / 2;
		int hy = y + (h * 2) / 3;
		for (i=0; i<hh; i++)
		{
			graphics->drawLine(hx - i + offset,
							   hy - i + offset,
							   hx + i + offset,
							   hy - i + offset);
		}
		
	} // end drawButton
    
	int DropDown::getSelected()
	{
		if (mScrollArea == NULL || mScrollArea->getContent() == NULL)
		{
			throw GCN_EXCEPTION("DropDown::getSelected. ScrollArea or ListBox is NULL");
		}

		return mListBox->getSelected();
		
	} // end getSelected
    
	void DropDown::setSelected(int selected)
	{
		if (mScrollArea == NULL || mScrollArea->getContent() == NULL)
		{
			throw GCN_EXCEPTION("DropDown::setSelected. ScrollArea or ListBox is NULL");
		}

		if (selected >= 0)
		{
			mListBox->setSelected(selected);
		}
		
	} // end setSelected
	
	void DropDown::keyPress(const Key& key)
	{
		if (mScrollArea == NULL || mScrollArea->getContent() == NULL)
		{
			throw GCN_EXCEPTION("DropDown::keyPress. ScrollArea or ListBox is NULL");
		}

		if ((key.getValue() == Key::ENTER || key.getValue() == Key::SPACE)
			&& !mDroppedDown)
		{
			dropDown();
			mFocusHandler.requestFocus(mScrollArea->getContent());
		}
		
	} // end keyPress
  
	void DropDown::mousePress(int x, int y, int button)
	{
		if (button == MouseInput::LEFT && hasMouse() && !mDroppedDown)
		{
			mPushed = true;
			dropDown();
		}
		// Fold up the listbox if the upper part is clicked after fold down
		else if (button == MouseInput::LEFT && hasMouse() && mDroppedDown
				 && y < mOldH)
		{
			foldUp();
		}
		else if (!hasMouse())
		{
			foldUp();
		}
		
	} // end mousePress

	void DropDown::mouseRelease(int x, int y, int button)
	{
		if (button == MouseInput::LEFT)
		{      
			mPushed = false;
		}

	} // end mouseRelease
  
	void DropDown::setListModel(ListModel *listModel)
	{
		if (mScrollArea == NULL || mScrollArea->getContent() == NULL)
		{
			throw GCN_EXCEPTION("DropDown::setListModel. ScrollArea or ListBox is NULL");
		}

		mListBox->setListModel(listModel);
    
		if (mListBox->getSelected() < 0)
		{
			mListBox->setSelected(0);
		}
    
		adjustHeight();
		
	} // end setListModel
  
	ListModel *DropDown::getListModel()
	{
		if (mScrollArea == NULL || mScrollArea->getContent() == NULL)
		{
			throw GCN_EXCEPTION("DropDown::getListModel. ScrollArea or ListBox is NULL");
		}
	  
		return mListBox->getListModel();
		
	} // end getListModel

	void DropDown::setScrollArea(ScrollArea *scrollArea)
	{
		mScrollArea->_setFocusHandler(NULL);
		mScrollArea->_setParent(NULL);
		mScrollArea = scrollArea;
		mScrollArea->_setFocusHandler(&mFocusHandler);
		mScrollArea->setContent(mListBox);
		mScrollArea->_setParent(this);
		adjustHeight();
		
	} // end setScrollArea

	ScrollArea *DropDown::getScrollArea()
	{
		return mScrollArea;
		
	} // end getScrollArea
  
	void DropDown::setListBox(ListBox *listBox)
	{
		listBox->setSelected(mListBox->getSelected());
		listBox->setListModel(mListBox->getListModel());
		listBox->addActionListener(this);

		if (mScrollArea->getContent() != NULL)
		{
			mListBox->removeActionListener(this);
		}
		
		mListBox = listBox;
    
		mScrollArea->setContent(mListBox);
    
		if (mListBox->getSelected() < 0)
		{
			mListBox->setSelected(0);
		}
		
	} // end setListBox

	ListBox *DropDown::getListBox()
	{
		return mListBox;
		
	} // end getListBox
  
	void DropDown::adjustHeight()
	{
		if (mScrollArea == NULL || mScrollArea->getContent() == NULL)
		{
			throw GCN_EXCEPTION("DropDown::adjustHeight. ScrollArea or ListBox is NULL");
		}

		int listBoxHeight = mListBox->getHeight();
		int h2 = getFont()->getHeight() + 2;

		setHeight(h2);
    
		if (mDroppedDown && getParent())
		{
			int h = getParent()->getHeight() - getY();
      
			if (listBoxHeight + 2 > h - h2)
			{
				mScrollArea->setHeight(h - h2);
				setHeight(h);
			}
			else
			{
				setHeight(listBoxHeight + h2 + 2);
				mScrollArea->setHeight(listBoxHeight + 2);
			}
		}

		mScrollArea->setWidth(getWidth());
		mScrollArea->setPosition(0, h2);
		
	} // end adjustHeight

	void DropDown::dropDown()
	{
		if (!mDroppedDown)
		{
			mDroppedDown = true;
			mOldH = getHeight();
			adjustHeight();

			if (getParent())
			{
				getParent()->moveToTop(this);
			}
		}
		
	} // end dropDown

	void DropDown::foldUp()
	{		
		if (mDroppedDown)
		{
			mDroppedDown = false;
			mFocusHandler.focusNone();
			adjustHeight();
		}
		
	} // end foldUp

	void DropDown::_keyInputMessage(const KeyInput& keyInput)
	{		
		if (mDroppedDown)
		{
			if (mScrollArea == NULL || mScrollArea->getContent() == NULL)
			{
				throw GCN_EXCEPTION("DropDown::_keyInputMessage. ScrollArea or ListBox is NULL");
			}

			if (mFocusHandler.getFocused() != NULL)
			{
				mFocusHandler.getFocused()->_keyInputMessage(keyInput);
			}
		}
		else
		{
			BasicContainer::_keyInputMessage(keyInput);
		}
		
	} // end _keyInputMessage
	
	void DropDown::_mouseInputMessage(const MouseInput &mouseInput)
	{	  	  
		BasicContainer::_mouseInputMessage(mouseInput);

		if (mDroppedDown)
		{
			if (mScrollArea == NULL || mScrollArea->getContent() == NULL)
			{
				throw GCN_EXCEPTION("DropDown::_mouseInputMessage. ScrollArea or ListBox is NULL");
			}
		  		  
			if (mouseInput.y >= mOldH)
			{
				MouseInput mi = mouseInput;
				mi.y -= mScrollArea->getY();        
				mScrollArea->_mouseInputMessage(mi);
			}
		}
		
	} // end _mouseInputMessage

	void DropDown::lostFocus()
	{
		foldUp();
		
	} // end lostFocus

	void DropDown::moveToTop(Widget* widget)
	{
		if (getParent())
		{
			getParent()->moveToTop(this);
		}
		
	} // end moveToTop

    void DropDown::moveToBottom(Widget* widget)
	{
		if (getParent())
		{
			getParent()->moveToBottom(this);
		}
		
	} // end moveToBottom

	void DropDown::_announceDeath(Widget* widget)
	{		
		if (widget == mScrollArea)
		{			
			mScrollArea = NULL;
		}
		else
		{
			throw GCN_EXCEPTION("DropDown::_announceDeath. Death announced for unknown widget.");
		}
		
	} // end _announceDeath

	void DropDown::action(const std::string& eventId)
	{
		foldUp();
		generateAction();
		
	} // end action

	void DropDown::getDrawSize(int& width, int& height, Widget* widget)
	{
		if (widget == mScrollArea)
		{
			if (mDroppedDown)
			{
				height = getHeight() - mOldH;
				width = getWidth();
			}
			else
			{
				width = height = 0;
			}
		}
		else
		{
			throw GCN_EXCEPTION("DropDown::getDrawSize. widget is not the ScrollArea (wieeerd...)");
		}
		
	} // end getDrawSize

	void DropDown::setBaseColor(const Color& color)
	{
		if (mDefaultScrollArea == mScrollArea && mScrollArea != NULL)
		{
			mScrollArea->setBaseColor(color);
		}

		if (mDefaultListBox == mListBox && mListBox != NULL)
		{
			mListBox->setBaseColor(color);
		}
				
		Widget::setBaseColor(color);
	}

	void DropDown::setBackgroundColor(const Color& color)
	{
		if (mDefaultScrollArea == mScrollArea && mScrollArea != NULL)
		{
			mScrollArea->setBackgroundColor(color);
		}

		if (mDefaultListBox == mListBox && mListBox != NULL)
		{
			mListBox->setBackgroundColor(color);
		}
				
		Widget::setBackgroundColor(color);
	}

	void DropDown::setForegroundColor(const Color& color)
	{
		if (mDefaultScrollArea == mScrollArea && mScrollArea != NULL)
		{
			mScrollArea->setForegroundColor(color);
		}

		if (mDefaultListBox == mListBox && mListBox != NULL)
		{
			mListBox->setForegroundColor(color);
		}
				
		Widget::setForegroundColor(color);
	} 
	
} // end gcn
