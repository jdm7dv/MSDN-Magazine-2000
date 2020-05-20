////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// Copyright (c) 1999  Microsoft Corporation.  All Rights Reserved.
// Written by Aaron Skonnard, http://www.skonnard.com
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//--------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AppHeadlines.h"
#include "HeadlineMgr.h"

/////////////////////////////////////////////////////////////////////////////
// CHeadlineMgr

STDMETHODIMP CHeadlineMgr::LoadHeadlines(VARIANT xmlHeadlines, VARIANT xmlMainStylesheet, VARIANT xmlNodeStylesheet)
{
    HRESULT hr;
    VARIANT_BOOL bSuccess;
    
    // synchronize access to this method
    Lock();

    m_bHeadlinesLoaded = FALSE;

    // load the static xml headline file and the appropriate stylesheet files
    // we need one stylesheet for transforming the entire document and one for 
    // individual node transformations
    hr = m_spDomDocHeadlines->load(xmlHeadlines, &bSuccess);
    CHECKRESULTS_UNLOCK(hr, bSuccess, "Error loading headlines XML file");
    hr = m_spDomDocStylesheet->load(xmlMainStylesheet, &bSuccess);
    CHECKRESULTS_UNLOCK(hr, bSuccess, "Error loading specified main stylesheet");
    hr = m_spDomDocStylesheetNode->load(xmlNodeStylesheet, &bSuccess);
    CHECKRESULTS_UNLOCK(hr, bSuccess, "Error loading specified node stylesheet");

    m_bHeadlinesLoaded = TRUE;

    // unlock critical section
    Unlock();

    return S_OK;
}

STDMETHODIMP CHeadlineMgr::PrintHeadlines(BSTR *bstrHeadlines)
{
    CComPtr<IXMLDOMElement> spStyleDocElement;
    CComPtr<IXMLDOMNode> spStyleDocNode;
    HRESULT hr;

    if (!m_bHeadlinesLoaded)
    {
        Error("Headlines must be loaded before calling PrintHeadlines", 0, 0, GUID_NULL, 0);
        return E_FAIL;
    }
    // get the stylesheet's document element
    hr = m_spDomDocStylesheet->get_documentElement(&spStyleDocElement);
    CHECKHR(hr, "Error retrieving stylesheet document element");
    hr = spStyleDocElement->QueryInterface(&spStyleDocNode);
    CHECKHR(hr, "Error retrieving stylesheet document element IXMLDOMNode interface");
    // transform the XML file using the loaded XSL file
    hr = m_spDomDocHeadlines->transformNode(spStyleDocNode, bstrHeadlines);
    CHECKHR(hr, "Error transforming XML headlines");
    
    return hr;
}

STDMETHODIMP CHeadlineMgr::PrintHeadlinesByCategory(BSTR bstrCategory, BSTR *bstrHeadlines)
{
    if (!m_bHeadlinesLoaded)
    {
        Error("Headlines must be loaded before calling PrintHeadlinesByCategory", 0, 0, GUID_NULL, 0);
        return E_FAIL;
    }

    // create pattern to filter by category
    CComBSTR bstrPattern("//Headline[Category = '");
    bstrPattern += bstrCategory;
    bstrPattern += "']";

    return PrintNodeList(bstrPattern, bstrHeadlines);
}

STDMETHODIMP CHeadlineMgr::PrintHotStories(BSTR *bstrHeadlines)
{
    if (!m_bHeadlinesLoaded)
    {
        Error("Headlines must be loaded before calling PrintHotStories", 0, 0, GUID_NULL, 0);
        return E_FAIL;
    }

    // create pattern to filter by HotStory attribute
    CComBSTR bstrPattern("//Headline[@HotStory = 'y']");

    return PrintNodeList(bstrPattern, bstrHeadlines);
}

STDMETHODIMP CHeadlineMgr::PrintHeadlinesByAffiliation(BSTR bstrAffiliation, BSTR *bstrHeadlines)
{
    if (!m_bHeadlinesLoaded)
    {
        Error("Headlines must be loaded before calling PrintHeadlinesByAffiliation", 0, 0, GUID_NULL, 0);
        return E_FAIL;
    }

    // create pattern to filter by affiliation
    CComBSTR bstrPattern("//Headline[Author/Affiliation = '");
    bstrPattern += bstrAffiliation;
    bstrPattern += "']";

    return PrintNodeList(bstrPattern, bstrHeadlines);
}

STDMETHODIMP CHeadlineMgr::PrintNodeList(BSTR bstrPattern, BSTR *bstrHeadlines)
{
    CComPtr<IXMLDOMElement> spStyleDocElement;
    CComPtr<IXMLDOMNode> spStyleDocNode;
    CComPtr<IXMLDOMNodeList> spNodeList;
    CComBSTR bstrNodeOutput;
    CComBSTR bstrOutput;
    HRESULT hr;
    long len;

    // get the document element of the stylesheet
    hr = m_spDomDocStylesheetNode->get_documentElement(&spStyleDocElement);
    CHECKHR(hr, "Error retrieving stylesheet document element");

    // get the IXMLDOMNode interface
    hr = spStyleDocElement->QueryInterface(&spStyleDocNode);
    CHECKHR(hr, "Error retrieving stylesheet document element IXMLDOMNode interface");
    
    // filter by category
    hr = m_spDomDocHeadlines->selectNodes(bstrPattern, &spNodeList);
    CHECKHR(hr, "Error selecting nodes with specified Category");

    // get the length of the resulting node list
    hr = spNodeList->get_length(&len);
    CHECKHR(hr, "Error retrieving node list length");

    // go through each node in the list and transform to HTML
    for (long i=0; i<len; i++)
    {
        CComPtr<IXMLDOMNode> spNode;
        hr = spNodeList->get_item(i, &spNode);
        CHECKHR(hr, "Error retrieving node from node list");

        hr = spNode->transformNode(spStyleDocNode, &bstrNodeOutput);
        if (SUCCEEDED(hr))
            bstrOutput += bstrNodeOutput;
        else
            Error("Error transforming XML document (m_spDomDocHeadlines->transformNode)", 0, 0, GUID_NULL, hr);
    }
    *bstrHeadlines = bstrOutput.Detach();

    return hr;
}

STDMETHODIMP CHeadlineMgr::AddHeadlineBatch(BSTR bstrNewXMLHeadlines)
{
    CComPtr<IXMLDOMDocument> spDomDocNewHeadlines;
    CComPtr<IXMLDOMNodeList> spNodeList;
    CComBSTR bstrPattern("//Headline");
    VARIANT_BOOL bSuccess;
    HRESULT hr;
    long len;

    Lock();

    // create a temporary instance of DOMFreeThreadedDocument
    hr = spDomDocNewHeadlines.CoCreateInstance(__uuidof(DOMFreeThreadedDocument));
    CHECKHR_UNLOCK(hr, "Error creating DOMFreeThreadedDocument coclass (new headlines)");

    // load the XML string that was passed in
    hr = spDomDocNewHeadlines->loadXML(bstrNewXMLHeadlines, &bSuccess);
    CHECKRESULTS_UNLOCK(hr, bSuccess, "Error loading new XML headline batch");
    
    // retrieve all the headline nodes
    hr = spDomDocNewHeadlines->selectNodes(bstrPattern, &spNodeList);
    CHECKHR_UNLOCK(hr, "Error selecting headline nodes");

    hr = spNodeList->get_length(&len);
    CHECKHR_UNLOCK(hr, "Error getting node list length");

    // go through the list of headline nodes and add them to the main document
    for (long i=0; i<len; i++)
    {
        CComPtr<IXMLDOMNode> spNode;
        CComPtr<IXMLDOMNode> spNodeOut;
        CComPtr<IXMLDOMNode> spClone;

        hr = spNodeList->get_item(i, &spNode);
        if (SUCCEEDED(hr))
        {
            CComPtr<IXMLDOMElement> spDocElement;
            
            hr = m_spDomDocHeadlines->get_documentElement(&spDocElement);
            CHECKHR_UNLOCK(hr, "Error getting headlines document element");
            hr = spDocElement->appendChild(spNode, &spNodeOut);
            CHECKHR_UNLOCK(hr, "Error appending new node to headline document");
        }
    }

    Unlock();

    return S_OK;
}

void CHeadlineMgr::Lock()
{
    EnterCriticalSection(&m_cs);
}

void CHeadlineMgr::Unlock()
{
    LeaveCriticalSection(&m_cs);
}
